#include "loginclientmanager.h"
#include "loginclient.h"

ITcpSocket * CLoginClientManager::OnAccept()
{
	ITcpSocket *pTcpSocket = new CLoginClient();
	if (nullptr == pTcpSocket)
	{
		return nullptr;
	}

	return pTcpSocket;
}

