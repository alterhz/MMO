#include "loginclient.h"
#include "loginc.h"

void CLoginClient::OnEstablish()
{
	LogDebug("��½��������������...");
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
	LogDebug("��½�������Ͽ���...");
}

