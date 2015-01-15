#include "common/thread.h"
#include "common/boostheader.h"

NS_LIB_HEADER;

bool IThread::Start()
{
	// 启动线程
	boost::thread t(boost::bind(&IThread::OnThreadRun, this));
	t.detach();

	return true;
}

// 信号量
Semaphore::Semaphore(unsigned int initialCount)
	: boost::interprocess::interprocess_semaphore(initialCount)
{
}
void Semaphore::Wait(unsigned int nWaitCount)
{
	for (unsigned int i=0; i<nWaitCount; ++i)
	{
		wait();
	}
}
void Semaphore::Post()
{
	post();
}

void Sleep(unsigned int nInterval)
{
	boost::this_thread::sleep(boost::posix_time::millisec(nInterval));
}

NS_LIB_FOOTER;

