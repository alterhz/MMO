#include "asio/tcpaccept.h"
#include "asio/tcpsocket.h"

#include "loginc.h"

ITcpAcceptor::ITcpAcceptor(IOS &ios)
	: m_ios(ios)
	, m_acceptor(m_ios)
	, m_pAcceptSocket(nullptr)
{
}

ITcpAcceptor::~ITcpAcceptor()
{
	m_acceptor.close();

	delete m_pAcceptSocket;
	m_pAcceptSocket = nullptr;
}

bool ITcpAcceptor::OpenAccept(const char * ip, unsigned short port)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	m_acceptor.open(ep.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
	boost::system::error_code ec;
	m_acceptor.bind(ep, ec);

	if (ec)
	{
		LogError(ec.message());
		return false;
	}

	m_acceptor.listen();

	DoAccept();

	return true;
}

void ITcpAcceptor::CancelAccept()
{
	m_acceptor.cancel();
}

bool ITcpAcceptor::DoAccept()
{
	m_pAcceptSocket = new boost::asio::ip::tcp::socket(m_ios);

	if (nullptr == m_pAcceptSocket)
	{
		return false;
	}

	m_acceptor.async_accept(*m_pAcceptSocket,
		bind(&ITcpAcceptor::OnAccept, this, boost::asio::placeholders::error));

	return true;
}

void ITcpAcceptor::OnAccept(const boost::system::error_code& ec)
{
	if (ec)
	{
		if (boost::asio::error::operation_aborted == ec.value())
		{

		}
		else
		{

		}

		return ;
	}

	ITcpSocket *pNewTcpSocket = OnAccept();
	if (nullptr == pNewTcpSocket)
	{
		return ;
	}

	pNewTcpSocket->InitSocket(m_pAcceptSocket);

	DoAccept();
}

