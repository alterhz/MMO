#include "worldconnector.h"
#include "loginc.h"

CWorldConnector::CWorldConnector( IOS &ios )
	: ITcpConnector(ios)
{
}

void CWorldConnector::OnEstablish()
{
	LogDebug("������WorldServer...");
}

void CWorldConnector::OnError( int nErrorCode )
{

}

bool CWorldConnector::OnRecvPacket( const char *pPacket, int nLength )
{

	return true;
}

void CWorldConnector::OnTerminate()
{

}



