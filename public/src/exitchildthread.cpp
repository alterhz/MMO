#include "exitchildthread.h"


bool CExitChildThread::OnThreadRun()
{
	m_semaExit.Wait();

	delete this;

	// 主线程退出，exit退出控制台线程循环
	exit(0);

	return true;
}

