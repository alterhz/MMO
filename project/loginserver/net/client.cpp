#include "client.h"

#include "loginc.h"


CClient::CClient()
{

}

void CClient::OnEstablish()
{
	//LogError("��������");

	//std::cout << "remote ip:" << GetRemoteIP() << ",port:" << GetRemotePort() << std::endl;
	//std::cout << "local ip:" << GetLocalIP() << ",port:" << GetLocalPort() << std::endl;
}

void CClient::OnError(int nErrorCode)
{
	LogError("Error");
}

bool CClient::OnRecvPacket(const char *pPacket, int nLength)
{
	//LogError("���յ�����");
	return true;
}

void CClient::OnTerminate()
{
	//LogError("�Ͽ�����");

	static int n = 0;
	std::cout << "delete client count:" << (++n) << std::endl;

	delete this;
}

