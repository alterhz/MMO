//----------------------------------------
// ����ʱ�� : 2014-12-25
// ���� : hanzhe
// ˵�� : main

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

			PrintInConsole("�ȴ����߳�ֹͣ...");
		}
	}

	return 0;
}