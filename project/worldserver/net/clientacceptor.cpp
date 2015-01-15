#include "clientacceptor.h"

#include "clientsocket.h"

CClientAcceptor::CClientAcceptor(IOS &ios)
	: ITcpAcceptor(ios)
	, m_pTmpSocket(nullptr)
{

}

CClientAcceptor::~CClientAcceptor()
{

}

ITcpSocket * CClientAcceptor::OnAccept()
{
	ITcpSocket *pTcpSocket = new CClientSocket();
	if (nullptr == pTcpSocket)
	{
		return nullptr;
	}

	m_pTmpSocket = pTcpSocket;

	return pTcpSocket;
}

void CClientAcceptor::CloseTmpSocket()
{
	if (m_pTmpSocket)
	{
		m_pTmpSocket->Close();
	}
}



