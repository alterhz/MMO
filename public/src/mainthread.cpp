#include "MainThread.h"

#include <iostream>
#include "loginc.h"
#include "common/file.h"
#include "app.h"
#include "exitchildthread.h"

CMainThread::CMainThread()
	: m_pExitChildThread(nullptr)
{
}

CMainThread::~CMainThread()
{
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

	CApp::getMe().Run();

	LogInfo("thread finished.");

	CApp::getMe().Release();

	if (m_pExitChildThread)
	{
		m_pExitChildThread->Post();
	}

	// É¾³ý×Ô¼º
	CMainThread::delMe();

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

	CApp::getMe().Stop();
}

