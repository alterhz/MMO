//----------------------------------------
// 创建时间 : 2014-11-13
// 作者 : hanzhe
// 说明 : 

#ifndef _ITCPACCEPTOR_H_
#define _ITCPACCEPTOR_H_

#include "interfacenet.h"
#include "header.h"


class CTcpAccept : public ITcpSocket
{
public:
	CTcpAccept(IIOServer &ioServer);
	virtual ~CTcpAccept();

	bool OpenAccept(const char * ip, unsigned short port);
	void CancelAccept();

private:
	bool DoAccept();
	void OnAccept(const boost::system::error_code& ec);


private:
	virtual ITcpSocket * OnNewTcpSocket() = 0;
	virtual void OnDelTcpSocket(ITcpSocket *pDelTcpSocket) = 0;


protected:
	IIOServer &m_ioServer;

private:
	boost::asio::ip::tcp::acceptor m_asioAccept;

	ITcpSocket *m_pListenTcpSocket;

	typedef std::vector<ITcpSocket *> VtTcpSocket;
	VtTcpSocket m_vtTcpSocket;
};

#endif