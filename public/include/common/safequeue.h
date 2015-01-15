//----------------------------------------
// ����ʱ�� : 2014-12-30
// ���� : hanzhe
// ˵�� : �̰߳�ȫ����

#ifndef _SAFEQUEUE_H_
#define _SAFEQUEUE_H_

#include "common/boostheader.h"

NS_LIB_HEADER;

struct BufferNode;

class CSafeQueue
{
public:
	CSafeQueue(int nNodeCount = 8);
	~CSafeQueue();

public:
	// ��ʼ������
	bool Init(int nNodeCount);

	// ѹ������
	bool Push(const char *pData, int nLength);

	// ��������
	bool Pop(const char * &pData, int &nLength);

	// �������
	void Clear();

private:
	BufferNode * CreateBufferNode();
	void DestoryBufferNode(BufferNode *pBufferNode);

private:
	// ��ȡ�ڵ���д��ڵ��γ�һ����������
	BufferNode *m_pWriteNode;
	BufferNode *m_pReadNode;

	int m_nNodeCount;

	boost::mutex m_lock;
};

NS_LIB_FOOTER;

#endif