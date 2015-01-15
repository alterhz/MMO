#include "common/timer.h"

NS_LIB_HEADER;

class CTimerInfo
{
public:
	CTimerInfo(IOS &ios, IEventTimer &eventTimer, int nTimerId, int nInterval)
		: m_deadlineTimer(ios)
		, m_eventTimer(eventTimer)
		, m_nTimerId(nTimerId)
		, m_nInterval(nInterval)
	{}
	~CTimerInfo()
	{
		if (m_deadlineTimer.cancel() > 0)
		{
			// 存在异步事件
		}
	}

public:
	void AsyncWait()
	{
		m_deadlineTimer.expires_from_now(boost::posix_time::millisec(m_nInterval));

		m_deadlineTimer.async_wait(boost::bind(&IEventTimer::OnTimerHandler, &m_eventTimer, 
			boost::asio::placeholders::error, m_nTimerId) );
	}
	void SetInterval(int nInterval) { m_nInterval = nInterval; }

private:
	boost::asio::deadline_timer m_deadlineTimer;
	IEventTimer &m_eventTimer;
	int m_nTimerId;
	unsigned int m_nInterval;
};

IEventTimer::IEventTimer(IOS &ios)
	: m_ios(ios)
{
}

IEventTimer::~IEventTimer()
{
	MapTimerInfo::iterator itTimerInfo = m_mapTimerInfo.begin();
	for (; itTimerInfo!=m_mapTimerInfo.end(); ++itTimerInfo)
	{
		if (nullptr != itTimerInfo->second)
		{
			delete itTimerInfo->second;
			itTimerInfo->second = nullptr;
		}
	}
	m_mapTimerInfo.clear();
}

bool IEventTimer::SetTimer(int nTimerId, int nInterval)
{
	CTimerInfo *pTimerInfo = FindTimerInfo(nTimerId);
	if (nullptr == pTimerInfo)
	{
		// 新的timer
		CTimerInfo *pTimerInfo = new CTimerInfo(m_ios, *this, nTimerId, nInterval);
		if (nullptr == pTimerInfo)
		{
			return false;
		}

		m_mapTimerInfo.insert(std::make_pair(nTimerId, pTimerInfo));

		pTimerInfo->AsyncWait();

		return true;
	}
	else
	{
		// 已存在的timer
		pTimerInfo->SetInterval(nInterval);

		pTimerInfo->AsyncWait();
	}

	return true;
}

void IEventTimer::KillTimer(int nTimerId)
{
	CTimerInfo *pTimerInfo = FindTimerInfo(nTimerId);
	if (pTimerInfo)
	{
		m_mapTimerInfo.erase(nTimerId);

		delete pTimerInfo;
		pTimerInfo = nullptr;
	}
}

CTimerInfo * IEventTimer::FindTimerInfo(int nTimerId)
{
	MapTimerInfo::iterator itTimerInfo = m_mapTimerInfo.find(nTimerId);
	if (itTimerInfo != m_mapTimerInfo.end())
	{
		return itTimerInfo->second;
	}

	return nullptr;
}

void IEventTimer::OnTimerHandler(const boost::system::error_code &ec, int nTimerId)
{
	if (ec)
	{
		if (boost::asio::error::operation_aborted == ec.value())
		{
			std::cout << "timer - operation_aborted" << std::endl;
		}

		std::cout << "timer - error" << std::endl;

		return ;
	}

	// 触发时间事件
	OnTimerEvent(nTimerId);

	// 再次投递异步时间事件
	CTimerInfo *pTimerInfo = FindTimerInfo(nTimerId);
	if (pTimerInfo)
	{
		pTimerInfo->AsyncWait();
	}
}

NS_LIB_FOOTER;
