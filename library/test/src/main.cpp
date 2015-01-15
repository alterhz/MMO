//----------------------------------------
// 创建时间 : 2014-12-26
// 作者 : hanzhe
// 说明 : 测试

#include <iostream>

#include "common/thread.h"
#include "common/file.h"
#include "common/timer.h"
#include "loginc.h"

void TestLog()
{
	G_pLog = new NSLIB::Log();
	if (nullptr == G_pLog)
	{
		return ;
	}

	std::string strPath = NSLIB::GetExeRootPath();
	strPath += "\\a.log";
	G_pLog->SetLogFilePath(strPath.c_str());
	G_pLog->Start();

	Sleep(1000);

	LogDebug("Log类型:DEBUG,int:" + 33 + ",bool:" + true);
	LogInfo("Log类型:INFO,int:" + 33 + ",bool:" + true);
	LogWarn("Log类型:WARN,int:" + 33 + ",bool:" + true);
	//LogError("Log类型:ERROR,int:" + 33 + ",bool:" + true);

	G_pLog->Stop();
	G_pLog->WaitFor();

	delete G_pLog;
	G_pLog = nullptr;
}

// timer_test
class CTimerTest : public NSLIB::IEventTimer
{
public:
	CTimerTest(IOS &ios)
		: IEventTimer(ios)
	{
	}
	~CTimerTest()
	{
		
	}

public:
	void Initailize()
	{
		SetTimer(1, 1000);
	}

protected:
	virtual void OnTimerEvent(int nTimerId)
	{
		std::cout << "ontimer! [ntimerid:" << nTimerId << "]" << std::endl;

		KillTimer(1);
	}
};

void TimerTest()
{
	IOS ios;
	boost::asio::io_service::work w(ios);
	
	CTimerTest *pTimerTest = new CTimerTest(ios);
	pTimerTest->Initailize();

	ios.run();
}

class CAThread : public NSLIB::IThread
{
public:
	virtual bool OnThreadRun()
	{
		NSLIB::Sleep(1000);

		int *p = nullptr;
		*p = 3;

		//assert(false);

		return true;
	}
};

class CBThread : public NSLIB::IThread
{
public:
	virtual bool OnThreadRun()
	{
		while(true)
		{
			NSLIB::Sleep(500);
			
			PrintInConsole("running");
		}
		

		return true;
	}
};

int main(int argc, char* argv[])
{
	CAThread a;
	a.Start();

	CBThread b;
	b.Start();

	system("pause");

	TimerTest();

	TestLog();

	//NSLIB::Semaphore sema(2);
	//sema.Wait(1);

	//std::cout << "finish" << std::endl;

	//sema.Wait();

	//std::cout << "end" << std::endl;

	//sema.Wait();

	return 0;
}