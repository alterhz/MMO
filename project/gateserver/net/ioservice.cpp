#include "ioservice.h"

#include "acceptclient.h"
#include "clientconnector.h"

CIOService::CIOService()
{

}

CIOService::~CIOService()
{

}

void CIOService::OnInitailize()
{
	// 监听客户端连接
	CAcceptClient *pAcceptClient = new CAcceptClient(*this);
	if (pAcceptClient)
	{
		pAcceptClient->OpenAccept("127.0.0.1", 8888);

		m_vtTcpAccept.push_back(pAcceptClient);
	}

	//ITcpConnector *pTcpConnector = new ITcpConnector();
	//if (pTcpConnector)
	//{
	//	pTcpConnector->BindIOS(this);
	//	pTcpConnector->Connect("127.0.0.1", 8888);
	//}

}

void CIOService::OnRelease()
{
	for (CTcpAccept *pDelTcpAccept : m_vtTcpAccept)
	{
		if (pDelTcpAccept)
		{
			pDelTcpAccept->CancelAccept();
			delete pDelTcpAccept;
			pDelTcpAccept = nullptr;
		}
	}
	m_vtTcpAccept.clear();
}

