//----------------------------------------
// 创建时间 : 2014-12-17
// 作者 : hanzhe
// 说明 : 连接器

#ifndef _TCPCONNECTOR_H_
#define _TCPCONNECTOR_H_

#include "asio/tcpsocket.h"
#include <string>

class ITcpConnector : public ITcpSocket
{
public:
	ITcpConnector(IOS &ios);
	virtual ~ITcpConnector();

	bool Connect(const char *pIP, unsigned short wPort);
	bool ReConnect();

private:
	void OnConnect(const boost::system::error_code& ec);

private:
	IOS &m_ios;
	boost::asio::ip::tcp::socket m_socket;
	std::string m_strIP;
	unsigned short m_wPort;

};

#endif