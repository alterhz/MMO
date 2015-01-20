//----------------------------------------
// ����ʱ�� : 2014-12-26
// ���� : hanzhe
// ˵�� : ���߼��߳�

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