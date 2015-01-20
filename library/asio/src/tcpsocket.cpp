#include "asio/tcpsocket.h"

#include "common/ringbuffer.h"
#include "loginc.h"

ITcpSocket::ITcpSocket()
	: m_pSocket(nullptr)
	, m_nAsyncEventCount(0)
	, m_nRecvLength(0)
	, m_nSendLength(0)
	, m_pRingBuffer(new CRingBuffer(0x2000))	//发送缓冲区大小
{
}

ITcpSocket::~ITcpSocket()
{
	delete m_pSocket;
	m_pSocket = nullptr;
	m_nRecvLength = 0;
	m_nSendLength = 0;
	delete m_pRingBuffer;
	m_pRingBuffer = nullptr;
}

bool ITcpSocket::InitSocket(boost::asio::ip::tcp::socket *pSocket)
{
	m_pSocket = pSocket;

	OnEstablish();

	DoRecv();

	return true;
}

bool ITcpSocket::DoRecv()
{
	char *pRecvBuffer = m_szRecvBuffer + m_nRecvLength;
	int nFreeRecvLength = MAX_RECV_BUFFER_LENGTH - m_nRecvLength;

	if (0 == nFreeRecvLength)
	{
		// 单个消息包过长，断开连接

		return false;
	}

	++m_nAsyncEventCount;

	m_pSocket->async_read_some(boost::asio::buffer(pRecvBuffer, nFreeRecvLength), 
		bind(&ITcpSocket::OnRecv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	return true;
}

bool ITcpSocket::OnRecv(const boost::system::error_code& ec, size_t nByteTransferred)
{
	--m_nAsyncEventCount;

	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted
			|| ec.value() == boost::asio::error::connection_reset
			|| ec.value() == boost::asio::error::eof
			|| ec.value() == boost::asio::error::bad_descriptor)
		{
			LogDebug(ec.message());
		}
		else
		{
			OnError(ec.value());
			LogError(ec.message());
		}

		Close();

		return false;
	}

	if (0 == nByteTransferred)
	{
		// 断开连接
		Close();

		return false;
	}

	m_nRecvLength += nByteTransferred;

	int nReadLength = 0;
	// 解析消息包
	do 
	{
		int nLeaftLength = m_nRecvLength - nReadLength;

		if (nLeaftLength < sizeof(unsigned short))
		{
			// 剩余不足消息包头长度
			break;
		}

		char *pPacketHeader = m_szRecvBuffer + nReadLength;
		unsigned short *pPacketLength = reinterpret_cast<unsigned short *>(pPacketHeader);
		unsigned short wPacketLength = *pPacketLength;

		if (nLeaftLength < static_cast<int>(sizeof(unsigned short) + wPacketLength))
		{
			// 剩余不足一个完整消息包
			break;
		}

		char *pDataHeader = m_szRecvBuffer + nReadLength + sizeof(unsigned short);
		int nPacketLength = static_cast<int>(wPacketLength);

		OnRecvPacket(pDataHeader, nPacketLength);

		nReadLength += sizeof(unsigned short);
		nReadLength += nPacketLength;
	} while (true);

	int nLeaftLength = m_nRecvLength - nReadLength;

	if (0 != nReadLength && 0 != nLeaftLength)
	{
		// 解析了消息包，但还剩余数据
		memmove(m_szRecvBuffer, m_szRecvBuffer + nReadLength, (m_nRecvLength - nReadLength));
		m_nRecvLength = nLeaftLength;
	}

	DoRecv();

	return true;
}

bool ITcpSocket::DoSend(const char *pBuffer, int nLength)
{
	char szData[MAX_SEND_BUFFER_LENGTH] = {0};
	unsigned short *pMessageLength = reinterpret_cast<unsigned short *>(szData);
	*pMessageLength = nLength;
	memcpy(szData + sizeof(unsigned short), pBuffer, nLength);

	if (!m_pRingBuffer->Write(szData, sizeof(unsigned short) + nLength))
	{
		LogWarn("发送缓冲区满，丢弃消息包.");
		return false;
	}

	if (0 == m_nSendLength)
	{
		int nReadLength = MAX_SEND_BUFFER_LENGTH - m_nSendLength;
		m_pRingBuffer->Read(m_szSendBuffer, nReadLength);

		m_nSendLength = nReadLength;

		// 发送数据
		if (m_nSendLength > 0)
		{
			++m_nAsyncEventCount;
			m_pSocket->async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
				bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}

	return true;
}

void ITcpSocket::OnSend(const boost::system::error_code &ec, size_t nByteTransferred)
{
	--m_nAsyncEventCount;
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted
			|| ec.value() == boost::asio::error::connection_reset
			|| ec.value() == boost::asio::error::eof
			|| ec.value() == boost::asio::error::bad_descriptor)
		{
			LogError(ec.message());
		}
		else
		{
			OnError(ec.value());
		}
		LogError(ec.message().c_str());

		Close();

		return ;
	}

	m_nSendLength -= nByteTransferred;

	if (m_nSendLength > 0)
	{
		memmove(m_szSendBuffer, m_szSendBuffer + nByteTransferred, m_nSendLength);
		
		++m_nAsyncEventCount;

		// 发送数据
		m_pSocket->async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
			bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	else if (0 == m_nSendLength)
	{
		int nReadLength = MAX_SEND_BUFFER_LENGTH - m_nSendLength;
		m_pRingBuffer->Read(m_szSendBuffer, nReadLength);

		m_nSendLength = nReadLength;

		// 发送数据
		if (m_nSendLength > 0)
		{
			++m_nAsyncEventCount;

			m_pSocket->async_write_some(boost::asio::buffer(m_szSendBuffer, m_nSendLength), 
				bind(&ITcpSocket::OnSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	else
	{
		LogError("[Net]异常错误！m_nSendLength:" + m_nSendLength);
	}
}

void ITcpSocket::Close()
{
	m_pSocket->shutdown(boost::asio::socket_base::shutdown_both);
	m_pSocket->close();

	if (0 == m_nAsyncEventCount)
	{
		OnClose();
	}
}

void ITcpSocket::OnClose()
{
	OnTerminate();
}

std::string ITcpSocket::GetRemoteIP() const
{
	if (m_pSocket)
	{
		return m_pSocket->remote_endpoint().address().to_string();
	}

	return "";
}

unsigned short ITcpSocket::GetRemotePort() const
{
	if (m_pSocket)
	{
		return m_pSocket->remote_endpoint().port();
	}

	return 0;
}

std::string ITcpSocket::GetLocalIP() const
{
	if (m_pSocket)
	{
		return m_pSocket->local_endpoint().address().to_string();
	}

	return "";
}

unsigned short ITcpSocket::GetLocalPort() const
{
	if (m_pSocket)
	{
		return m_pSocket->local_endpoint().port();
	}

	return 0;
}
