//----------------------------------------
// 创建时间 : 2014-11-1
// 作者 : hanzhe
// 说明 : 

#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <memory.h>

class CRingBuffer
{
public:
	CRingBuffer(int nLength);
	~CRingBuffer();

public:
	// 写入
	bool Write(const char *pData, int nLength);
	// 读取
	bool Read(char *pData, int &nLength);


private:
	char *m_pData;
	int m_nLength;

	int m_nWritePos;
	int m_nReadPos;
};

#endif