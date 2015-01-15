#include "ioserver.h"

#include "tcpaccept.h"
#include "tcpconnector.h"

CIOServer::CIOServer()
	: m_pIOServerCallBack(nullptr)
	, m_pWork(nullptr)
{
}

CIOServer::~CIOServer()
{
	delete m_pWork;
	m_pWork = nullptr;

	m_ios.stop();
	
	m_pIOServerCallBack = nullptr;
}

bool CIOServer::Start(IIOServerCallback *pIOServerCallBack)
{
	if (nullptr == pIOServerCallBack)
	{
		return false;
	}

	m_pIOServerCallBack = pIOServerCallBack;

	m_pWork = new boost::asio::io_service::work(m_ios);

	return true;
}

bool CIOServer::Stop()
{
	delete m_pWork;
	m_pWork = nullptr;
	return true;
}

void CIOServer::Run()
{
_run:
	try
	{
		m_ios.run();
	}
	catch (boost::system::system_error &e)
	{
		LogError(e.what());

		goto _run;
	}

	if (m_pIOServerCallBack)
	{
		m_pIOServerCallBack->OnStop();
	}
}

void CIOServer::Poll()
{
	m_ios.poll();
}

bool CIOServer::Post(ITask *pTask)
{
	m_ios.dispatch(boost::bind(&ITask::OnExcute, pTask));
	return true;
}
