#include "clientsocket.h"

#include "protoinc.h"
#include "loginc.h"

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::OnEstablish()
{
	LogError("��������");

	//Close();
}

void CClientSocket::OnError(int nErrorCode)
{
	LogError("���ִ���");
}

bool CClientSocket::OnRecvPacket(const char *pPacket, int nLength)
{
	LogError(pPacket);

	gproto::MSG_G2C_PING msgG2CPing;
	if (!msgG2CPing.ParseFromArray(pPacket, nLength))
	{
		LogError("����ʧ��");
		return true;
	}

	std::cout << msgG2CPing.count() << std::endl;

	return true;
}

void CClientSocket::OnTerminate()
{
	LogError("�Ͽ�����");
}
