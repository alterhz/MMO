#include "MainThread.h"

#include <iostream>
#include "loginc.h"
#include "common/file.h"
#include "app.h"
#include "exitchildthread.h"

CMainThread::CMainThread()
	: m_pWork(nullptr)
	, m_pExitChildThread(nullptr)
{
}

CMainThread::~CMainThread()
{
	delete m_pWork;
	m_pWork = nullptr;
}

bool CMainThread::OnThreadRun()
{
	bool bInitOk = CApp::getMe().Init();
	if (!bInitOk)
	{
		CApp::getMe().Release();

		return false;
	}

	LogInfo("thread begin...");

	m_pWork = new boost::asio::io_service::work(m_ios);

_run:
	try
	{
		m_ios.run();
	}
	catch (boost::system::error_code &e)
	{
		LogError(e.message());
		goto _run;
	}

	LogInfo("thread finished.");

	CApp::getMe().Release();


	if (m_pExitChildThread)
	{
		m_pExitChildThread->Post();
	}

	// É¾³ý×Ô¼º
	delete this;

	return true;
}

void CMainThread::Stop()
{
	if (nullptr == m_pExitChildThread)
	{
		CExitChildThread *pExitChildThread = new CExitChildThread();
		if (nullptr == pExitChildThread)
		{
			return ;
		}

		m_pExitChildThread = pExitChildThread;

		m_pExitChildThread->Start();
	}

	delete m_pWork;
	m_pWork = nullptr;
}

