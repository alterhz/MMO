//----------------------------------------
// ����ʱ�� : 2014-12-25
// ���� : hanzhe
// ˵�� : �ͻ��˶��������

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