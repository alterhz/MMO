//----------------------------------------
// ����ʱ�� : 2014-12-25
// ���� : hanzhe
// ˵�� : main

#include <iostream>

#include "MainThread.h"
#include "loginc.h"

int main(int argc, char *argv[])
{
	CMainThread *pMainThead = new CMainThread();
	if (pMainThead)
	{
		pMainThead->Start();
	}

	while (true)
	{
		std::string strIn;
		std::cin >> strIn;

		if ("exit" == strIn)
		{
			pMainThead->Stop();

			PrintInConsole("�ȴ����߳�ֹͣ...");
		}
	}

	return 0;
}