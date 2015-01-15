//----------------------------------------
// 创建时间 : 2014-12-25
// 作者 : hanzhe
// 说明 : 客户端对象管理器

#ifndef _CLIENTMANAGER_H_
#define _CLIENTMANAGER_H_

#include "asioinc.h"

class CClientManager : public ITcpAcceptor
{
public:
	CClientManager(IOS &iso);

public:
	virtual ITcpSocket * OnAccept();
	virtual bool OnClose(ITcpSocket *pDelTcpSocket);
};

#endif