//----------------------------------------
// ����ʱ�� : 2015-1-10
// ���� : hanzhe
// ˵�� : loginclient����

#ifndef _LOGINMANAGER_H_
#define _LOGINMANAGER_H_

#include "asioinc.h"

class CLoginClientManager : public ITcpAcceptor
{
public:
	CLoginClientManager(IOS &ios)
		: ITcpAcceptor(ios)
	{
	}
	~CLoginClientManager() {}

public:
	virtual ITcpSocket * OnAccept();

};

#endif