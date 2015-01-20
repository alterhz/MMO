#include "app.h"

#include "loginc.h"
#include "common/file.h"
#include "netmanager.h"

CApp::CApp()
	: m_pWork(nullptr)
{
}

CApp::~CApp()
{
}

bool CApp::Init()
{
	if (!InitLog())
	{
		return false;
	}

	if (!InitRes())
	{
		return false;
	}

	if (!InitNet())
	{
		return false;
	}

	return true;
}

void CApp::Release()
{
	PrintInConsole("app release");

	// É¾³ý
	CNetManager::delMe();

	// ×îºóÍ£Ö¹log
	if (G_pLog)
	{
		G_pLog->Stop();
		G_pLog->WaitFor();

		delete G_pLog;
		G_pLog = nullptr;
	}
}

bool CApp::InitLog()
{
	G_pLog = new NSLIB::Log();
	if (nullptr == G_pLog)
	{
		return false;
	}

	std::string strPath = NSLIB::GetExeRootPath();
	strPath += "\\worldserver.log";
	G_pLog->SetLogFilePath(strPath.c_str());

	// Æô¶¯log
	return G_pLog->Start();
}

bool CApp::InitRes()
{
	return true;
}

bool CApp::InitNet()
{
	CNetManager::getMe().InitNetManager(m_ios);

	return true;
}

void CApp::Run()
{
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
}

void CApp::Stop()
{
	// Í£Ö¹ÍøÂç¼àÌý
	CNetManager::getMe().StopNetManager();

	delete m_pWork;
	m_pWork = nullptr;
}

