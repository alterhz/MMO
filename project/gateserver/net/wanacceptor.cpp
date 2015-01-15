#include "wanacceptor.h"

#include "wansocket.h"

CWanAcceptor::CWanAcceptor(IOS &ios)
	: ITcpAcceptor(ios)
{

}

CWanAcceptor::~CWanAcceptor()
{

}

ITcpSocket * CWanAcceptor::OnAccept()
{
	return new CWanSocket();
}

bool CWanAcceptor::OnClose(ITcpSocket *pDelTcpSocket)
{

	return true;
}



