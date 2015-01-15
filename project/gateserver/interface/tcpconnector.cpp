#include "tcpconnector.h"

#include "ioservice.h"

ITcpConnector::ITcpConnector(CIOServer &ioService)
	: ITcpSocket(ioService)
	, m_strRemoteIP("")
	, m_wRemotePort(0)
{
}

ITcpConnector::~ITcpConnector()
{
	m_strRemoteIP.clear();
	m_wRemotePort = 0;
}

bool ITcpConnector::Connect(const char *pRemoteIP, unsigned short wRemotePort)
{
	m_strRemoteIP = pRemoteIP;
	m_wRemotePort = wRemotePort;

	boost::asio::ip::tcp::endpoint epRemote(boost::asio::ip::address::from_string(pRemoteIP), wRemotePort);

	m_asioSocket.async_connect(epRemote, 
		bind(&ITcpConnector::OnConnect, this, boost::asio::placeholders::error));

	return true;
}

void ITcpConnector::OnConnect(const boost::system::error_code& ec)
{
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted)
		{

		}
		else
		{

		}

		return ;
	}
}

