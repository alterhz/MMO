//----------------------------------------
// 创建时间 : 2014-12-26
// 作者 : hanzhe
// 说明 : 主逻辑线程

#ifndef _MAINTHREAD_H_
#define _MAINTHREAD_H_

#include "common/thread.h"
#include "utility.h"

class CExitChildThread;

class CMainThread : public NSLIB::IThread, public Singleton<CMainThread>
{
public:
	CMainThread();
	~CMainThread();

	void Stop();

protected:
	virtual bool OnThreadRun();

private:
	
	CExitChildThread *m_pExitChildThread;
};

#endif