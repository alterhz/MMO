#include "acceptormanager.h"

#include "loginclientmanager.h"

CAcceptorManager::CAcceptorManager()
	: m_pLoginClientManager(nullptr)
{
}

CAcceptorManager::~CAcceptorManager()
{

}

bool CAcceptorManager::InitNetManager(IOS &ios)
{
	m_pLoginClientManager = new CLoginClientManager(ios);
	if (m_pLoginClientManager)
	{
		m_pLoginClientManager->OpenAccept("127.0.0.1", 1000);
	}



	return true;
}

void CAcceptorManager::StopNetManager()
{
	delete m_pLoginClientManager;
	m_pLoginClientManager = nullptr;
}

