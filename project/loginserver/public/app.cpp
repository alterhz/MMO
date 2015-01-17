#include "app.h"

#include "loginc.h"
#include "common/file.h"

CApp::CApp()
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
	strPath += "\\loginserver.log";
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
	return true;
}

