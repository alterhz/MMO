//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 应用程序启动

#ifndef _APP_H_
#define _APP_H_

#include "utility.h"

class CApp : public Singleton<CApp>
{
public:
	CApp();
	~CApp();

public:
	bool Init();
	void Release();

private:
	bool InitLog();
	bool InitRes();
	bool InitNet();

};

#endif