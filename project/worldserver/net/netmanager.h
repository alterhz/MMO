//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 监听管理器

#ifndef _NETMANAGER_H_
#define _NETMANAGER_H_

#include "asioinc.h"
#include "utility.h"

class CLoginClientManager;

class CNetManager : public Singleton<CNetManager>
{
public:
	CNetManager();
	~CNetManager();

	bool InitNetManager(IOS &ios);

	void StopNetManager();

private:
	CLoginClientManager *m_pLoginClientManager;
};

#endif