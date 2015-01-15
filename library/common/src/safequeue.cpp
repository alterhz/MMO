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
	// Ĭ�ϲ�����128KB
	CBuffer(int nLength = 0x20000);
	~CBuffer();

public:
	void Clear();
	// д��
	bool Write(const char *pData, int nLength);
	// ��ȡ
	bool Read(const char * &pData, int &nLength);
	// ��ȡ���
	bool ReadComplete() const { return (m_nReadPos >= m_nWritePos); }

private:
	bool IsValidePos(int nPos) const;
	DataNode * GetWriteNode(int nLength) const;
	const DataNode * GetReadNode() const;

private:
	char *m_pData;
	int m_nLength;

	// д��λ��
	int m_nWritePos;

	// ��ȡλ��
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

		// �γ�����
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
		// д��ʧ�ܣ��ƶ�д��ڵ�
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
		// ��ǰ�ڵ��ȡ��ϣ��л�����һ���ڵ�
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
			// û�����ݣ�˵��׷����д��ڵ�
			m_lock.unlock();
			return false;
		}

		// �任��ȡ�ڵ�
		m_pReadNode = pNextBufferNode;

		// �����ǰ�ڵ�����д�룬��д��ڵ����
		if (m_pReadNode == m_pWriteNode)
		{
			m_pWriteNode = m_pWriteNode->next;
		}

		m_lock.unlock();
	}

	// ��ȡ�ڵ�����
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
	// ��������
	memcpy(pWriteNode->szData, pData, nLength);

	// �ƶ�д��λ��
	m_nWritePos += (sizeof(unsigned short) + nLength);

	return true;
}

bool CBuffer::Read(const char * &pData, int &nLength)
{
	if (m_nReadPos >= m_nWritePos)
	{
		// �Ѿ���ȡ��ĩβ
		return false;
	}

	// ��ȡ��ǰ�ڵ�
	const DataNode *pNode = GetReadNode();
	if (nullptr == pNode)
	{
		return false;
	}

	nLength = pNode->wLength;
	pData = &(pNode->szData[0]);

	// �ƶ���ȡλ��[ע�⣺��������ƶ���ȡλ�ã�����Ϊд�벻����ǰ��д�룬�������ݲ��ᱻ�޸�]
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
