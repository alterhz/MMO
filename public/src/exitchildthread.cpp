#include "exitchildthread.h"


bool CExitChildThread::OnThreadRun()
{
	m_semaExit.Wait();

	delete this;

	// ���߳��˳���exit�˳�����̨�߳�ѭ��
	exit(0);

	return true;
}

