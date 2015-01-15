//----------------------------------------
// 创建时间 : 2014-12-30
// 作者 : hanzhe
// 说明 : 线程安全队列

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
	// 初始化链表
	bool Init(int nNodeCount);

	// 压入数据
	bool Push(const char *pData, int nLength);

	// 弹出数据
	bool Pop(const char * &pData, int &nLength);

	// 清空数据
	void Clear();

private:
	BufferNode * CreateBufferNode();
	void DestoryBufferNode(BufferNode *pBufferNode);

private:
	// 读取节点与写入节点形成一个环形链表
	BufferNode *m_pWriteNode;
	BufferNode *m_pReadNode;

	int m_nNodeCount;

	boost::mutex m_lock;
};

NS_LIB_FOOTER;

#endif