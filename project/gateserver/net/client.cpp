#include "client.h"


CClient::CClient(CIOServer &ioService)
	: ITcpSocket(ioService)
{
}

CClient::~CClient()
{

}

bool CClient::OnRecvPacket(const char *pPacket, int nLength)
{
	LogError(pPacket);

	return true;
}
