//----------------------------------------
// 创建时间 : 2015-1-13
// 作者 : hanzhe
// 说明 : 退出子线程

#ifndef _EXITCHILDTHREAD_H_
#define _EXITCHILDTHREAD_H_

#include "common/thread.h"

class CExitChildThread : public NSLIB::IThread
{
public:
	virtual bool OnThreadRun();

public:
	void Post() { m_semaExit.Post(); }

private:
	NSLIB::Semaphore m_semaExit;
};

#endif