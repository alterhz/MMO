//----------------------------------------
// 创建时间 : 2014-12-27
// 作者 : hanzhe
// 说明 : log

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

	// 绝对路径 例如：\log\debug\test.log
	void SetLogFilePath(const char *pLogPath);
	// 写入log
	void Write(const char *pLogType, const char *pLogData);
	// 启动log
	bool Start();
	// 停止log
	void Stop() { m_bRunning = false; }
	// 等待停止
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