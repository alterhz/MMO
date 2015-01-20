#include "netmanager.h"

#include "loginclientmanager.h"

CNetManager::CNetManager()
	: m_pLoginClientManager(nullptr)
{
}

CNetManager::~CNetManager()
{

}

bool CNetManager::InitNetManager(IOS &ios)
{
	m_pLoginClientManager = new CLoginClientManager(ios);
	if (m_pLoginClientManager)
	{
		m_pLoginClientManager->OpenAccept("127.0.0.1", 8000);
	}

	return true;
}

void CNetManager::StopNetManager()
{
	delete m_pLoginClientManager;
	m_pLoginClientManager = nullptr;
}

