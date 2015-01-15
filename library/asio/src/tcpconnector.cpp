#include "asio/tcpconnector.h"

#include "loginc.h"

ITcpConnector::ITcpConnector(IOS &ios)
	: m_ios(ios)
	, m_socket(m_ios)
	, m_strIP("")
	, m_wPort(0)
{
}

ITcpConnector::~ITcpConnector()
{
	m_socket.shutdown(boost::asio::socket_base::shutdown_both);
	m_socket.close();
}

bool ITcpConnector::Connect(const char *pIP, unsigned short wPort)
{
	m_strIP = pIP;
	m_wPort = wPort;

	ReConnect();

	return true;
}

bool ITcpConnector::ReConnect()
{
	if (m_socket.is_open())
	{
		LogError("连接状态不能重连。");
		return false;
	}

	boost::asio::ip::tcp::endpoint epRemote(boost::asio::ip::address::from_string(m_strIP), m_wPort);

	m_socket.async_connect(epRemote, 
		bind(&ITcpConnector::OnConnect, this, boost::asio::placeholders::error));

	LogError("重连服务器");

	return true;
}

void ITcpConnector::OnConnect(const boost::system::error_code& ec)
{
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted)
		{
			LogError(ec.message());
		}
		else
		{
			OnError(ec.value());
		}

		return ;
	}

	InitSocket(&m_socket);
}

