#include "lanworldsocket.h"

#include "protoinc.h"

CLanWorldSocket::CLanWorldSocket(IOS &ios)
	: ITcpConnector(ios)
{

}

bool CLanWorldSocket::OnRecvPacket(const char *pPacket, int nLength)
{

	return true;
}

void CLanWorldSocket::OnEstablish()
{
	//LogError("connector���ӳɹ���");

	//static int i = 0;
	//
	//gproto::MSG_G2C_PING msgG2CPing;
	//msgG2CPing.set_count(++i);

	//char szSend[0x2000] = {0};
	//if (!msgG2CPing.SerializePartialToArray(szSend, 0x2000))
	//{
	//	LogError("����ʧ��");
	//	return ;
	//}

	//DoSend(szSend, msgG2CPing.ByteSize());
}

