#include "common/log.h"
#include "common/safequeue.h"

NSLIB::Log *G_pLog = nullptr;

NS_LIB_HEADER;

class CLogFile
{
public:
	CLogFile(const char *pFilePath);
	~CLogFile();

public:
	bool Open(const char *pFilePath);
	void Write(const char *pText);

private:
	std::ofstream m_fs;
};

CLogFile::CLogFile(const char *pFilePath)
{
	Open(pFilePath);
}

CLogFile::~CLogFile()
{
	m_fs.close();
}

bool CLogFile::Open(const char *pFilePath)
{
	if (!m_fs.is_open())
	{
		m_fs.open(pFilePath, std::ios_base::app);
	}

	return m_fs.is_open();
}

void CLogFile::Write(const char *pText)
{
	m_fs << pText << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// log
Log::Log() : m_pLogFile(nullptr)
	, m_bRunning(true)
	, m_sema(0)
	, m_pSafeQueue(new CSafeQueue())
{
}

Log::~Log()
{
	delete m_pLogFile;
	m_pLogFile = nullptr;
	delete m_pSafeQueue;
	m_pSafeQueue = nullptr;
}

void Log::Write(const char *pLogType, const char *pLogData)
{
	if (!m_bRunning)
	{
		// 提示
		return ;
	}

	// 拼接数据
	std::string strTime = boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::local_time());
	int pos = strTime.find('T');
	strTime.replace(pos, 1, std::string(" "));

	//std::string strData = std::string("[") + pLogType + "]" + pLogData + "[" + strTime.c_str() + "]";
	std::string strData = std::string("[") + strTime.c_str() + " - " + pLogType + "]" + pLogData;

	if (m_pSafeQueue)
	{
		m_pSafeQueue->Push(strData.c_str(), strData.length() + 1);
	}
}

bool Log::OnThreadRun()
{
	assert(!(nullptr == m_pLogFile));
	assert(!(nullptr == m_pSafeQueue));

	while (m_bRunning)
	{
		const char *pText = nullptr;
		int nLength = 0;
		if (m_pSafeQueue->Pop(pText, nLength))
		{
			// 有数据
			m_pLogFile->Write(pText);

			std::cout << pText << std::endl;
		}
		else
		{
			Sleep(1);	//休息一下
		}
	}

	while (true)
	{
		const char *pText = nullptr;
		int nLength = 0;
		if (m_pSafeQueue->Pop(pText, nLength))
		{
			// 有数据
			m_pLogFile->Write(pText);
		}
		else
		{
			break;
		}
	}

	// 线程退出信号
	m_sema.Post();
	
	return true;
}

void Log::SetLogFilePath(const char *pLogPath)
{
	if (nullptr == m_pLogFile)
	{
		m_pLogFile = new CLogFile(pLogPath);	
	}

	if (m_pLogFile)
	{
		m_pLogFile->Open(pLogPath);
	}
}

void Log::WaitFor()
{
	if (!m_bRunning)
	{
		m_sema.Wait();
	}
}

bool Log::Start()
{
	// 启动线程
	return IThread::Start();
}

NS_LIB_FOOTER;