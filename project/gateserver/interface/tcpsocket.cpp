#include "tcpsocket.h"

CTcpSocket::CTcpSocket(CIOServer &ioService)
	: m_ioService(ioService)
	, m_asioSocket(ioService.m_ios)
	, m_nRecvLength(0)
	, m_nSendLength(0)
	, m_ringBuffer(0x8000)	//发送缓冲区大小
{
	DoRecv();
}

CTcpSocket::~CTcpSocket()
{
	m_asioSocket.close();
	m_nRecvLength = 0;
	m_nSendLength = 0;
}

bool CTcpSocket::DoRecv()
{
	char *pRecvBuffer = m_szRecvBuffer + m_nRecvLength;
	int nFreeRecvLength = MAX_RECV_BUFFER_LENGTH - m_nRecvLength;

	if (0 == nFreeRecvLength)
	{
		// 单个消息包过长，断开连接

		return false;
	}

	m_asioSocket.async_read_some(boost::asio::buffer(pRecvBuffer, nFreeRecvLength), 
		bind(&ITcpSocket::OnRecv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	return true;
}

bool CTcpSocket::OnRecv(const boost::system::error_code& ec, size_t nByteTransferred)
{
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted
			|| ec.value() == boost::asio::error::connection_reset
			|| ec.value() == boost::asio::error::eof
			|| ec.value() == boost::asio::error::bad_descriptor)
		{

		}
		else
		{
			OnError(ec.value());
		}

		return false;
	}

	m_nRecvLength += nByteTransferred;

	OnRecvPacket(m_szRecvBuffer, m_nRecvLength);

	DoRecv();

	return true;
}

bool CTcpSocket::DoSend(const char *pBuffer, int nLength)
{
	char szData[MAX_SEND_BUFFER_LENGTH] = {0};
	unsigned short *pMessageLength = reinterpret_cast<unsigned short *>(szData);
	*pMessageLength = nLength;
	memcpy(szData + sizeof(unsigned short), pBuffer, nLength);

	if (!m_ringBuffer.Write(szData, sizeof(unsigned short) + nLength))
	{
		LogError("发送缓冲区满，丢弃消息包.");
		return false;
	}

	if (0 == m_nSendLength)
	{
		int nReadLength = MAX_SEND_BUFFER_LENGTH - m_nSendLength;
		m_ringBuffer.Read(m_szSendBuffer, nReadLength);

		m_nSendLength = nReadLength;

		// 发送数据
		if (m_nSendLength > 0)
		{
			m_asioSocket.async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
				bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	
	return true;
}

void CTcpSocket::OnSend(const boost::system::error_code &ec, size_t nByteTransferred)
{
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted
			|| ec.value() == boost::asio::error::connection_reset
			|| ec.value() == boost::asio::error::eof
			|| ec.value() == boost::asio::error::bad_descriptor)
		{

		}
		else
		{
			OnError(ec.value());
		}
		LogError(ec.message().c_str());

		return ;
	}

	m_nSendLength -= nByteTransferred;

	if (m_nSendLength > 0)
	{
		memmove(m_szSendBuffer, m_szSendBuffer + nByteTransferred, m_nSendLength);

		// 发送数据
		m_asioSocket.async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
			bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	else if (0 == m_nSendLength)
	{
		int nReadLength = MAX_SEND_BUFFER_LENGTH - m_nSendLength;
		m_ringBuffer.Read(m_szSendBuffer, nReadLength);

		m_nSendLength = nReadLength;

		// 发送数据
		if (m_nSendLength > 0)
		{
			m_asioSocket.async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
				bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	else
	{
		LogError("[Net]异常错误！m_nSendLength:" + m_nSendLength);
	}
}

void CTcpSocket::Close()
{
	m_asioSocket.close();
}

void CTcpSocket::OnClose()
{
	
}
