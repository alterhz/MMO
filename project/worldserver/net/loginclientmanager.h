//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : loginclient管理

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