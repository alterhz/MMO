#include "loginclient.h"
#include "loginc.h"

void CLoginClient::OnEstablish()
{
	LogDebug("登陆服务器连接上了...");
}

void CLoginClient::OnError(int nErrorCode)
{

}

bool CLoginClient::OnRecvPacket(const char *pPacket, int nLength)
{

	return true;
}

void CLoginClient::OnTerminate()
{
	LogDebug("登陆服务器断开了...");
}

