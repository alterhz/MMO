//----------------------------------------
// ����ʱ�� : 2014-12-26
// ���� : hanzhe
// ˵�� : ���߼��߳�

#ifndef _MAINTHREAD_H_
#define _MAINTHREAD_H_

#include "common/thread.h"

class CClientManager;

class CMainThread : public NSLIB::IThread
{
public:
	CMainThread();
	~CMainThread();

	void Stop();

protected:
	virtual bool OnThreadRun();
	void OnRelease();

private:
	IOS m_ios;
	boost::asio::io_service::work *m_pWork;
	CExitChildThread *m_pExitChildThread;
};

#endif