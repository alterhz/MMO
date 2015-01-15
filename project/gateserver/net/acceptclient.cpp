#include "acceptclient.h"

#include "client.h"

CAcceptClient::CAcceptClient(IIOServer &ioServer)
	: ITcpAccept(ioServer)
{
}

CAcceptClient::~CAcceptClient()
{

}

ITcpSocket * CAcceptClient::OnNewTcpSocket()
{
	// [ToDo]
	return new CClient(m_ioServer);
}

void CAcceptClient::OnDelTcpSocket(ITcpSocket *pDelTcpSocket)
{
	delete pDelTcpSocket;
	pDelTcpSocket = nullptr;
}
