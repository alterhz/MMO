//----------------------------------------
// 创建时间 : 2014-12-12
// 作者 : hanzhe
// 说明 : 网络接收

#ifndef _ITCPACCEPT_H_
#define _ITCPACCEPT_H_

#include "common/boostheader.h"

class ITcpSocket;

class ITcpAcceptor
{
public:
	ITcpAcceptor(IOS &iso);
	virtual ~ITcpAcceptor();

	bool OpenAccept(const char * ip, unsigned short port);
	void CancelAccept();


private:
	bool DoAccept();
	void OnAccept(const boost::system::error_code& ec);


protected:
	virtual ITcpSocket * OnAccept() = 0;
	//virtual bool OnClose(ITcpSocket *pDelTcpSocket) = 0;


protected:
	IOS &m_ios;

private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::ip::tcp::socket *m_pAcceptSocket;
};

#endif