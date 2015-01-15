//----------------------------------------
// ����ʱ�� : 2014-11-1
// ���� : hanzhe
// ˵�� : 

#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <memory.h>

class CRingBuffer
{
public:
	CRingBuffer(int nLength);
	~CRingBuffer();

public:
	// д��
	bool Write(const char *pData, int nLength);
	// ��ȡ
	bool Read(char *pData, int &nLength);
	// �����Զ�����
	void SetAutoIncrease() { m_bAutoIncrease = true; }

private:
	// ����
	bool ReAlloc(int nLength);


private:
	char *m_pData;
	int m_nLength;

	int m_nWritePos;
	int m_nReadPos;

	// �Զ�����
	bool m_bAutoIncrease;
};

#endif