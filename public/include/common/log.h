//----------------------------------------
// ����ʱ�� : 2014-12-27
// ���� : hanzhe
// ˵�� : log

#ifndef _LOG_H_
#define _LOG_H_

#include "common/boostheader.h"
#include "common/thread.h"

NS_LIB_HEADER;

class CLogFile;
class CSafeQueue;

class Log : public IThread
{
public:
	Log();
	~Log();

	// ����·�� ���磺\log\debug\test.log
	void SetLogFilePath(const char *pLogPath);
	// д��log
	void Write(const char *pLogType, const char *pLogData);
	// ����log
	bool Start();
	// ֹͣlog
	void Stop() { m_bRunning = false; }
	// �ȴ�ֹͣ
	void WaitFor();

protected:
	virtual bool OnThreadRun();

private:
	CLogFile *m_pLogFile;
	bool m_bRunning;
	Semaphore m_sema;
	CSafeQueue *m_pSafeQueue;
};

NS_LIB_FOOTER;

#endif