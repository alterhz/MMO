//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 应用程序启动

#ifndef _APP_H_
#define _APP_H_

#include "common/thread.h"
#include "utility.h"

class CApp : public IAppInterface, public Singleton<CApp>
{
public:
	CApp();
	~CApp();

public:
	virtual bool Init();
	virtual void Release();
	virtual void Run();
	virtual void Stop();

private:
	bool InitLog();
	bool InitRes();
	bool InitNet();

private:
	IOS m_ios;
	boost::asio::io_service::work *m_pWork;
};

#endif