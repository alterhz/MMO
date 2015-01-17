//----------------------------------------
// 创建时间 : 2014-11-25
// 作者 : hanzhe
// 说明 : 应用程序入口文件，应用程序入口函数main。


#include <iostream>

#include "asioinc.h"
#include "wanacceptor.h"
#include "lanworldsocket.h"

#include "common/thread.h"
#include "loginc.h"

int main(int argc, char *argv[])
{
	IOS ios;

	boost::asio::io_service::work work(ios);

	CWanAcceptor acceptor(ios);
	acceptor.OpenAccept("127.0.0.1", 8880);

	for (int i=0; i<10000; ++i)
	{
		NSLIB::Sleep(1);
		CLanWorldSocket *pWorld = new CLanWorldSocket(ios);
		pWorld->Connect("192.168.17.106", 9005);
	}

_run:
	try
	{
		ios.run();
	}
	catch (boost::system::error_code &e)
	{
		LogError(e.message());
		goto _run;
	}

	return 0;
}