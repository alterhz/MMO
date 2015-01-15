//----------------------------------------
// 创建时间 : 2014-11-29
// 作者 : hanzhe
// 说明 : 接收客户端连接

#ifndef _ACCEPTCLIENT_H_
#define _ACCEPTCLIENT_H_

#include "interfacenet.h"

class CAcceptClient : public ITcpAcceptCallback
{
public:
	CAcceptClient(IIOServer &ioServer);
	~CAcceptClient();

public:
	virtual bool OnAccept(ITcpSocket * s) = 0;
	virtual bool OnClose() = 0;

private:
	ITcpAccept *m_pTcpAccept;

};

#endif