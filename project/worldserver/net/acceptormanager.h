//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 监听管理器

#ifndef _ACCEPTORMANAGER_H_
#define _ACCEPTORMANAGER_H_

#include "asioinc.h"
#include "utility.h"

class CLoginClientManager;

class CAcceptorManager : public Singleton<CAcceptorManager>
{
public:
	CAcceptorManager();
	~CAcceptorManager();

	bool InitNetManager(IOS &ios);

	void StopNetManager();

private:
	CLoginClientManager *m_pLoginClientManager;
};

#endif