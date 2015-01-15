//----------------------------------------
// 创建时间 : 2014-10-31
// 作者 : hanzhe
// 说明 : 

#ifndef _ITCPSOCKET_H_
#define _ITCPSOCKET_H_

#include "header.h"
#include "ringbuffer.h"
#include "ioservice.h"

#define MAX_RECV_BUFFER_LENGTH		(0x2000)
#define MAX_SEND_BUFFER_LENGTH		(0x2000)


class CTcpSocket
{
	friend class CTcpAccept;

public:
	CTcpSocket(CIOServer &ioService);
	virtual ~CTcpSocket();

public:
	bool DoSend(const char *pBuffer, int nLength);
	void Close();

private:
	bool DoRecv();

private:
	virtual void OnEstablish() = 0;
	virtual void OnError(int nErrorCode) = 0;
	virtual bool OnRecvPacket(const char *pPacket, int nLength) = 0;
	virtual void OnTerminate() = 0;


private:
	bool OnRecv(const boost::system::error_code& ec, size_t nByteTransferred);
	void OnSend(const boost::system::error_code &ec, size_t nByteTransferred);
	void OnClose();

protected:
	CIOServer &m_ioService;
	boost::asio::ip::tcp::socket m_asioSocket;

private:
	char m_szRecvBuffer[MAX_RECV_BUFFER_LENGTH];
	int m_nRecvLength;
	char m_szSendBuffer[MAX_SEND_BUFFER_LENGTH];
	int m_nSendLength;

	// 发送缓冲区
	CRingBuffer m_ringBuffer;
};


#endif