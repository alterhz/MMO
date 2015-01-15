//----------------------------------------
// ����ʱ�� : 2014-11-26
// ���� : hanzhe
// ˵�� : ������

#ifndef _ITCPCONNECTOR_H_
#define _ITCPCONNECTOR_H_

#include "header.h"
#include "itcpsocket.h"

class CIOServer;

class ITcpConnector : public ITcpSocket
{
public:
	ITcpConnector(CIOServer &ioService);
	virtual ~ITcpConnector();

public:
	bool Connect(const char *pRemoteIP, unsigned short wRemotePort);

private:
	void OnConnect(const boost::system::error_code& ec);

private:
	std::string m_strRemoteIP;
	unsigned short m_wRemotePort;

};

#endif