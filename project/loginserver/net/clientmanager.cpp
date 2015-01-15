#include "clientmanager.h"

#include "client.h"

CClientManager::CClientManager(IOS &iso)
	: ITcpAcceptor(iso)
{
}

ITcpSocket * CClientManager::OnAccept()
{
	CClient *pNewClient = new CClient();
	if (nullptr == pNewClient)
	{
		std::cout << "new Client error." << std::endl;
		return nullptr;
	}

	
	static int n = 0;
	++n;
	if (n % 1000 == 0)
	{
		std::cout << "new client count:" << n << std::endl;
	}

	return pNewClient;
}

bool CClientManager::OnClose(ITcpSocket *pDelTcpSocket)
{
	return true;
}


