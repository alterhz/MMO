//----------------------------------------
// 创建时间 : 2014-12-26
// 作者 : hanzhe
// 说明 : 线程库

#ifndef _THREAD_H_
#define _THREAD_H_

#include "common/boostheader.h"

NS_LIB_HEADER;

class IThread
{
public:
	virtual ~IThread() {}

	bool Start();

protected:
	virtual bool OnThreadRun() = 0;
};

void Sleep(unsigned int nInterval);

// 信号量
class Semaphore : private boost::interprocess::interprocess_semaphore
{
public:
	Semaphore(unsigned int initialCount = 0);

public:
	void Wait(unsigned int nWaitCount = 1);
	void Post();
};

NS_LIB_FOOTER;

#endif