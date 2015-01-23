#include "client.h"

#include "loginc.h"
#include "protoinc.h"
#include "worldconnector.h"
#include "netmanager.h"

CClient::CClient()
	: m_eClientStatus(EStatus_NotLoginIn)
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
	if (nLength < sizeof(unsigned short))
	{
		LogError("消息长度不足Length:" + nLength);
		return false;
	}

	const unsigned short *pMsgId = reinterpret_cast<const unsigned short *>(pPacket);
	unsigned short wMsgId = *pMsgId;

	const void *pProtoData = static_cast<const void *>(pPacket + sizeof(unsigned short));
	int nProtoLength = nLength - sizeof(unsigned short);

	switch (m_eClientStatus)
	{
	case EStatus_NotLoginIn:
		OnNotLoginInLogicDispatch(wMsgId, pProtoData, nProtoLength);
		break;
	case EStatus_HaveLoginIn:
		OnHaveLoginInLogicDispatch(wMsgId, pProtoData, nProtoLength);
		break;
	default:
		break;
	}


	return true;
}

void CClient::OnTerminate()
{
	//LogError("断开连接");

	static int n = 0;
	std::cout << "delete client count:" << (++n) << std::endl;

	delete this;
}

void CClient::OnNotLoginInLogicDispatch( unsigned short wMsgId, const void *pProtoData, int nProtoLength )
{
	switch (wMsgId)
	{
	case gproto::CSID_C2G_AccountLogin:
		{
			CWorldConnector *pWorldConnector = CNetManager::getMe().GetWorldConnector();
			if (pWorldConnector)
			{
				pWorldConnector->SendProtoData(wMsgId, pProtoData, nProtoLength);
			}
		}
		break;
	default:
		break;
	}
}

void CClient::OnHaveLoginInLogicDispatch( unsigned short wMsgId, const void *pProtoData, int nProtoLength )
{
	switch (wMsgId)
	{
	case gproto::CSID_C2G_GetGateInfo:
		{
			CWorldConnector *pWorldConnector = CNetManager::getMe().GetWorldConnector();
			if (pWorldConnector)
			{
				pWorldConnector->SendProtoData(wMsgId, pProtoData, nProtoLength);
			}
		}
		break;
	default:
		break;
	}
}

