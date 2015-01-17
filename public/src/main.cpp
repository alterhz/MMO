//----------------------------------------
// 创建时间 : 2014-12-25
// 作者 : hanzhe
// 说明 : main

#include <iostream>

#include "MainThread.h"
#include "loginc.h"

int main(int argc, char *argv[])
{
	CMainThread::getMe().Start();

	while (true)
	{
		std::string strIn;
		std::cin >> strIn;

		if ("exit" == strIn)
		{
			if (CMainThread::instance())
			{
				CMainThread::instance()->Stop();
			}

			PrintInConsole("等待主线程停止...");
		}
	}

	return 0;
}