#include "worldconnector.h"
#include "loginc.h"

CWorldConnector::CWorldConnector( IOS &ios )
	: ITcpConnector(ios)
{
}

void CWorldConnector::OnEstablish()
{
	LogDebug("连接上WorldServer...");

	gproto::MSG_C2G_PING msgPing;
	msgPing.set_count(1);

	Send(gproto::CSID_C2G_PING, &msgPing);
}

void CWorldConnector::OnError( int nErrorCode )
{

}

bool CWorldConnector::OnRecvPacket( const char *pPacket, int nLength )
{
	if (nLength < sizeof(unsigned short))
	{
		LogError("消息长度不足Length:" + nLength);
		return false;
	}

	const unsigned short *pMsgId = reinterpret_cast<const unsigned short *>(pPacket);
	unsigned short wMsgId = *pMsgId;

	const void *pProtoData = static_cast<const void *>(pPacket + sizeof(unsigned short));
	int nProtoLength = nLength - sizeof(unsigned short);

	switch (wMsgId)
	{
	case gproto::CSID_G2C_PING:
		{
			gproto::MSG_G2C_PING msgG2CPing;
			if (!msgG2CPing.ParseFromArray(pProtoData, nProtoLength))
			{
				LogError("协议解码失败：" + wMsgId);
				return false;
			}

			LogDebug("count:" + msgG2CPing.count());

			if (msgG2CPing.count() < 10)
			{
				gproto::MSG_C2G_PING msgPing;
				msgPing.set_count(msgG2CPing.count() + 1);

				Send(gproto::CSID_C2G_PING, &msgPing);
			}
		}
		break;
	default:
		break;
	}

	return true;
}

void CWorldConnector::OnTerminate()
{

}

bool CWorldConnector::Send( unsigned short wMsgId, google::protobuf::Message *pMessage )
{
	char szBuffer[0x2000] = {0};
	unsigned short *pMsgId = reinterpret_cast<unsigned short *>(szBuffer);
	*pMsgId = wMsgId;

	char *pProtoHeader = szBuffer + sizeof(unsigned short);

	if (!pMessage->SerializePartialToArray(pProtoHeader, 0x2000-sizeof(unsigned short)))
	{
		LogError("协议编码失败：" + wMsgId);
		return false;
	}

	int nBufferLength = sizeof(unsigned short) + pMessage->ByteSize();

	return DoSend(szBuffer, nBufferLength);
}

bool CWorldConnector::SendAccountLogin( const char *pAccount )
{
	gproto::MSG_C2G_AccountLogin msgAccountLogin;
	msgAccountLogin.set_account(pAccount);

	return Send(gproto::CSID_C2G_AccountLogin, &msgAccountLogin);
}

bool CWorldConnector::SendProtoData( unsigned short wMsgId, const void *pProtoData, int nProtoLength )
{
	char szBuffer[0x2000] = {0};
	unsigned short *pMsgId = reinterpret_cast<unsigned short *>(szBuffer);
	*pMsgId = wMsgId;

	char *pProtoHeader = szBuffer + sizeof(unsigned short);

	memcpy(pProtoHeader, pProtoData, nProtoLength);
	int nBufferLength = sizeof(unsigned short) + nProtoLength;

	return DoSend(szBuffer, nBufferLength);
}



