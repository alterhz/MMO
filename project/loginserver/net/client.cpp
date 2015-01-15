#include "client.h"

#include "loginc.h"


CClient::CClient()
{

}

void CClient::OnEstablish()
{
	//LogError("建立连接");

	//std::cout << "remote ip:" << GetRemoteIP() << ",port:" << GetRemotePort() << std::endl;
	//std::cout << "local ip:" << GetLocalIP() << ",port:" << GetLocalPort() << std::endl;
}

void CClient::OnError(int nErrorCode)
{
	LogError("Error");
}

bool CClient::OnRecvPacket(const char *pPacket, int nLength)
{
	//LogError("接收到数据");
	return true;
}

void CClient::OnTerminate()
{
	//LogError("断开连接");

	static int n = 0;
	std::cout << "delete client count:" << (++n) << std::endl;

	delete this;
}

