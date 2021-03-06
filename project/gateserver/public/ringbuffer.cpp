#include "ringbuffer.h"

CRingBuffer::CRingBuffer(int nLength)
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

CRingBuffer::~CRingBuffer()
{

}

bool CRingBuffer::Write(const char *pData, int nLength)
{
	if (m_nWritePos >= m_nReadPos)
	{
		int nFreeLength = m_nLength - m_nWritePos + m_nReadPos;
		if (nLength > nFreeLength)
		{
			// 空闲空间不足
			return false;
		}

		int nWriteToEnd = m_nLength - m_nWritePos;
		if (nLength > nWriteToEnd)
		{
			memcpy(m_pData + m_nWritePos, pData, nWriteToEnd);
			memcpy(m_pData, pData + nWriteToEnd, nLength - nWriteToEnd);
			m_nWritePos = nLength - nWriteToEnd;
		}
		else
		{
			memcpy(m_pData + m_nWritePos, pData, nLength);
			m_nWritePos += nLength;
		}
	}
	else
	{
		int nFreeLength = m_nReadPos - m_nWritePos;
		if (nLength > nFreeLength)
		{
			// 空闲空间不足
			return false;
		}

		memcpy(m_pData + m_nWritePos, pData, nLength);
		m_nWritePos += nLength;
	}

	return true;
}

bool CRingBuffer::Read(char *pData, int &nLength)
{
	if (m_nWritePos >= m_nReadPos)
	{
		int nUsedLength = m_nWritePos - m_nReadPos;

		if (nLength >= nUsedLength)
		{
			memcpy(pData, m_pData + m_nReadPos, nUsedLength);
			m_nReadPos += nUsedLength;
			nLength = nUsedLength;
		}
		else
		{
			memcpy(pData, m_pData + m_nReadPos, nLength);
			m_nReadPos += nLength;
			nLength = nLength;
		}
	}
	else
	{
		int nReadToEnd = m_nLength - m_nReadPos;

		if (nLength > nReadToEnd)
		{
			int nUsedLength = m_nLength - m_nReadPos + m_nWritePos;

			if (nLength > nUsedLength)
			{
				// 数据全部读取完
				memcpy(pData, m_pData + m_nReadPos, nReadToEnd);
				memcpy(pData + nReadToEnd, m_pData, nUsedLength - nReadToEnd);
				m_nReadPos = m_nWritePos;
				nLength = nUsedLength;
			}
			else
			{
				// 空间不足，没有读取完
				memcpy(pData, m_pData + m_nReadPos, nReadToEnd);
				memcpy(pData + nReadToEnd, m_pData, nLength - nReadToEnd);
				m_nReadPos = nLength - nReadToEnd;
				nLength = nLength;
			}
		}
		else
		{
			memcpy(pData, m_pData + m_nReadPos, nLength);
			m_nReadPos += nLength;
			nLength = nLength;
		}
	}

	return true;
}
