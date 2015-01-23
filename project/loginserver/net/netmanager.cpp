#include "netmanager.h"

#include "worldconnector.h"

CNetManager::CNetManager()
	: m_pIos(nullptr)
	, m_pWorldConnector(nullptr)
{

}

CNetManager::~CNetManager()
{

}

bool CNetManager::InitNet( IOS *pIos )
{
	if (nullptr == pIos)
	{
		return false;
	}

	m_pIos = pIos;

	// Á¬½ÓworldServer
	CWorldConnector *pWorldConnector = new CWorldConnector(*m_pIos);
	if (pWorldConnector)
	{
		pWorldConnector->Connect("127.0.0.1", 8000);
	}

	return true;
}


