#include "loginclient.h"
#include "loginc.h"
#include "protoinc.h"

void CLoginClient::OnEstablish()
{
	LogDebug("��½��������������...");
}

void CLoginClient::OnError(int nErrorCode)
{

}

bool CLoginClient::OnRecvPacket(const char *pPacket, int nLength)
{
	if (nLength < sizeof(unsigned short))
	{
		LogError("��Ϣ���Ȳ���Length:" + nLength);
		return false;
	}

	const unsigned short *pMsgId = reinterpret_cast<const unsigned short *>(pPacket);
	unsigned short wMsgId = *pMsgId;
	
	const void *pProtoData = static_cast<const void *>(pPacket + sizeof(unsigned short));
	int nProtoLength = nLength - sizeof(unsigned short);

	switch (wMsgId)
	{
	case gproto::CSID_C2G_PING:
		{
			gproto::MSG_C2G_PING msgC2GPing;
			if (!msgC2GPing.ParseFromArray(pProtoData, nProtoLength))
			{
				LogError("Э�����ʧ�ܣ�" + wMsgId);
				return false;
			}

			LogDebug("count:" + msgC2GPing.count());

			gproto::MSG_G2C_PING msgPing;
			msgPing.set_count(msgC2GPing.count());

			Send(gproto::CSID_G2C_PING, &msgPing);
		}
		break;
	default:
		break;
	}

	


	return true;
}

void CLoginClient::OnTerminate()
{
	LogDebug("��½�������Ͽ���...");
}

bool CLoginClient::Send( unsigned short wMsgId, google::protobuf::Message *pMessage )
{
	char szBuffer[0x2000] = {0};
	unsigned short *pMsgId = reinterpret_cast<unsigned short *>(szBuffer);
	*pMsgId = wMsgId;

	char *pProtoHeader = szBuffer + sizeof(unsigned short);

	if (!pMessage->SerializePartialToArray(pProtoHeader, 0x2000-sizeof(unsigned short)))
	{
		LogError("Э�����ʧ�ܣ�" + wMsgId);
		return false;
	}

	int nProtoLength = sizeof(unsigned short) + pMessage->ByteSize();

	return DoSend(szBuffer, nProtoLength);
}

