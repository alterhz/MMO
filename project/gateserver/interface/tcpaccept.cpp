#include "tcpaccept.h"
#include "ioservice.h"

#include "tcpsocket.h"

CTcpAccept::CTcpAccept(IIOServer &ioServer)
	: m_ioServer(ioServer)
	, m_asioAccept(m_ioServer.m_ios)
	, m_pListenTcpSocket(nullptr)
{
}

CTcpAccept::~CTcpAccept()
{
	m_asioAccept.close();
	m_pListenTcpSocket = nullptr;
}

bool CTcpAccept::OpenAccept(const char * ip, unsigned short port)
{
	boost::system::error_code ec;
	m_asioAccept.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), ec);

	if (ec)
	{
		LogError(ec.message());

		return false;
	}

	DoAccept();

	return true;
}

bool CTcpAccept::DoAccept()
{
	m_pListenTcpSocket = OnNewTcpSocket();
	if (nullptr == m_pListenTcpSocket)
	{
		return false;
	}

	m_asioAccept.async_accept(m_pListenTcpSocket->m_asioSocket,
		bind(&CTcpAccept::OnAccept, this, boost::asio::placeholders::error));

	return true;
}

void CTcpAccept::OnAccept(const boost::system::error_code& ec)
{
	if (ec)
	{
		if (boost::asio::error::operation_aborted == ec.value())
		{

		}
		else
		{

		}

		OnDelTcpSocket(m_pListenTcpSocket);
		m_pListenTcpSocket = nullptr;

		return ;
	}

	DoAccept();
}

void CTcpAccept::CancelAccept()
{
	m_asioAccept.cancel();
}

