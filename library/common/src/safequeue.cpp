#include "common/safequeue.h"

NS_LIB_HEADER;

struct DataNode
{
	DataNode()
	{

	}
	DataNode(const char *pBuffer)
		: wLength(0)
	{
		const unsigned short *pLength = reinterpret_cast<const unsigned short *>(pBuffer);
		wLength = *pLength;
	}

	unsigned short wLength;
	char szData[1];
};

class CBuffer
{
public:
	// 默认参数：128KB
	CBuffer(int nLength = 0x20000);
	~CBuffer();

public:
	void Clear();
	// 写入
	bool Write(const char *pData, int nLength);
	// 读取
	bool Read(const char * &pData, int &nLength);
	// 读取完毕
	bool ReadComplete() const { return (m_nReadPos >= m_nWritePos); }

private:
	bool IsValidePos(int nPos) const;
	DataNode * GetWriteNode(int nLength) const;
	const DataNode * GetReadNode() const;

private:
	char *m_pData;
	int m_nLength;

	// 写入位置
	int m_nWritePos;

	// 读取位置
	int m_nReadPos;
};

struct BufferNode
{
	BufferNode()
		: next(nullptr)
		, buffer(0x20000)
	{
	}

	//BufferNode *prev;
	BufferNode *next;

	CBuffer buffer;
};

CSafeQueue::CSafeQueue(int nNodeCount)
	: m_pWriteNode(nullptr)
	, m_pReadNode(nullptr)
	, m_nNodeCount(nNodeCount)
{
	Init(nNodeCount);
}

CSafeQueue::~CSafeQueue()
{
	Clear();
}

BufferNode * CSafeQueue::CreateBufferNode()
{
	return new BufferNode();
}

void CSafeQueue::DestoryBufferNode(BufferNode *pBufferNode)
{
	delete pBufferNode;
	pBufferNode = nullptr;
}

bool CSafeQueue::Init(int nNodeCount)
{
	if (nNodeCount < 2)
	{
		return false;
	}

	BufferNode *pPrevNode = CreateBufferNode();
	if (nullptr == pPrevNode)
	{
		return false;
	}

	m_pWriteNode = pPrevNode;

	for (int i=1; i<nNodeCount; ++i)
	{
		BufferNode *pNextNode = CreateBufferNode();
		if (nullptr == pNextNode)
		{
			return false;
		}

		// 形成链表
		pPrevNode->next = pNextNode;
		pPrevNode = pNextNode;
	}

	if (nullptr == pPrevNode)
	{
		return false;
	}

	m_pReadNode = pPrevNode;
	m_pReadNode->next = m_pWriteNode;

	m_nNodeCount = nNodeCount;

	return true;
}

bool CSafeQueue::Push(const char *pData, int nLength)
{
	m_lock.lock();

	if (nullptr == m_pWriteNode)
	{
		m_lock.unlock();
		return false;
	}

	if (m_pWriteNode->buffer.Write(pData, nLength))
	{
		m_lock.unlock();
		return true;
	}

	if (nullptr != m_pWriteNode->next 
		&& m_pWriteNode->next != m_pReadNode)
	{
		// 写入失败，移动写入节点
		m_pWriteNode = m_pWriteNode->next;

		if (m_pWriteNode->buffer.Write(pData, nLength))
		{
			m_lock.unlock();
			return true;
		}
	}

	m_lock.unlock();

	return false;
}

bool CSafeQueue::Pop(const char * &pData, int &nLength)
{
	if (nullptr == m_pReadNode)
	{
		return false;
	}

	if (m_pReadNode->buffer.ReadComplete())
	{
		// 当前节点读取完毕，切换到下一个节点
		m_pReadNode->buffer.Clear();

		m_lock.lock();

		BufferNode *pNextBufferNode = m_pReadNode->next;
		if (nullptr == pNextBufferNode)
		{
			m_lock.unlock();
			return false;
		}

		if (pNextBufferNode->buffer.ReadComplete())
		{
			// 没有数据，说明追到了写入节点
			m_lock.unlock();
			return false;
		}

		// 变换读取节点
		m_pReadNode = pNextBufferNode;

		// 如果当前节点正在写入，将写入节点后移
		if (m_pReadNode == m_pWriteNode)
		{
			m_pWriteNode = m_pWriteNode->next;
		}

		m_lock.unlock();
	}

	// 读取节点数据
	return m_pReadNode->buffer.Read(pData, nLength);
}

void CSafeQueue::Clear()
{
	BufferNode *pCurNode = m_pReadNode;

	do 
	{
		if (nullptr == pCurNode)
		{
			break;
		}

		BufferNode *pDelNode = pCurNode;
		pCurNode = pCurNode->next;

		delete pDelNode;
		pDelNode = nullptr;

	} while (pCurNode != m_pReadNode);

	m_pWriteNode = nullptr;
	m_pReadNode = nullptr;
}

// buffer
CBuffer::CBuffer(int nLength /*= 0x20000*/)
	: m_pData(nullptr)
	, m_nLength(0)
	, m_nWritePos(0)
	, m_nReadPos(0)
{
	if (nLength > 0)
	{
		m_pData = new char[nLength];
		m_nLength = nLength;
	}
}

CBuffer::~CBuffer()
{
	delete m_pData;
	m_pData = nullptr;
}

bool CBuffer::IsValidePos(int nPos) const
{
	if (nPos >= 0 && nPos < m_nLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CBuffer::Clear()
{
	m_nWritePos = 0;
	m_nReadPos = 0;
}

bool CBuffer::Write(const char *pData, int nLength)
{
	if (nLength <= 0)
	{
		return false;
	}

	DataNode *pWriteNode = GetWriteNode(nLength);
	if (nullptr == pWriteNode)
	{
		return false;
	}

	pWriteNode->wLength = nLength;
	// 拷贝数据
	memcpy(pWriteNode->szData, pData, nLength);

	// 移动写入位置
	m_nWritePos += (sizeof(unsigned short) + nLength);

	return true;
}

bool CBuffer::Read(const char * &pData, int &nLength)
{
	if (m_nReadPos >= m_nWritePos)
	{
		// 已经读取到末尾
		return false;
	}

	// 获取当前节点
	const DataNode *pNode = GetReadNode();
	if (nullptr == pNode)
	{
		return false;
	}

	nLength = pNode->wLength;
	pData = &(pNode->szData[0]);

	// 移动读取位置[注意：这里可以移动读取位置，是因为写入不会再前面写入，并且数据不会被修改]
	m_nReadPos += (sizeof(unsigned short) + pNode->wLength);

	return true;
}

const DataNode * CBuffer::GetReadNode() const
{
	if (nullptr == m_pData)
	{
		return nullptr;
	}

	if (!IsValidePos(m_nReadPos))
	{
		return nullptr;
	}

	const char *pReadHead = &(m_pData[m_nReadPos]);

	const DataNode *pNode = reinterpret_cast<const DataNode *>(pReadHead);

	return pNode;
}

DataNode * CBuffer::GetWriteNode(int nLength) const
{
	if (nullptr == m_pData)
	{
		return nullptr;
	}

	if (nLength <= 0)
	{
		return nullptr;
	}

	if (!IsValidePos(m_nWritePos))
	{
		return nullptr;
	}

	if (!IsValidePos(m_nWritePos + nLength))
	{
		return nullptr;
	}

	char *pWrite = &(m_pData[m_nWritePos]);

	DataNode *pNode = reinterpret_cast<DataNode *>(pWrite);

	return pNode;
}

NS_LIB_FOOTER;
