#ifndef _ITCPSOCKET_H_
#define _ITCPSOCKET_H_

#include "common/boostheader.h"

#define MAX_RECV_BUFFER_LENGTH		(0x20)
#define MAX_SEND_BUFFER_LENGTH		(0x20)

class CRingBuffer;

class ITcpSocket
{
	friend class ITcpAcceptor;

public:
	ITcpSocket();
	virtual ~ITcpSocket();

public:
	bool InitSocket(boost::asio::ip::tcp::socket *pSocket);
	bool DoSend(const char *pBuffer, int nLength);
	void Close();
	// ��ȡԶ��IP��Port
	std::string GetRemoteIP() const;
	unsigned short GetRemotePort() const;
	// ��ȡ����IP��Port
	std::string GetLocalIP() const;
	unsigned short GetLocalPort() const;

protected:
	virtual void OnEstablish() = 0;
	virtual void OnError(int nErrorCode) = 0;
	virtual bool OnRecvPacket(const char *pPacket, int nLength) = 0;
	virtual void OnTerminate() = 0;

private:
	bool DoRecv();
	// �¼�
	bool OnRecv(const boost::system::error_code& ec, size_t nByteTransferred);
	void OnSend(const boost::system::error_code &ec, size_t nByteTransferred);
	void OnClose();

private:
	boost::asio::ip::tcp::socket *m_pSocket;
	int m_nAsyncEventCount;

	char m_szRecvBuffer[MAX_RECV_BUFFER_LENGTH];
	int m_nRecvLength;
	char m_szSendBuffer[MAX_SEND_BUFFER_LENGTH];
	int m_nSendLength;

	// ���ͻ�����
	CRingBuffer *m_pRingBuffer;
};

#endif