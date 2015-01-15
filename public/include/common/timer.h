//----------------------------------------
// 创建时间 : 2015-1-6
// 作者 : hanzhe
// 说明 : 时间相关

#ifndef _TIMER_H_
#define _TIMER_H_

#include "common/boostheader.h"

NS_LIB_HEADER;

class CTimerInfo;

class IEventTimer
{
	friend class CTimerInfo;
public:
	IEventTimer(IOS &ios);
	~IEventTimer();

public:
	bool SetTimer(int nTimerId, int nInterval);
	void KillTimer(int nTimerId);

private:
	void OnTimerHandler(const boost::system::error_code &ec, int nTimerId);

protected:
	virtual void OnTimerEvent(int nTimerId) = 0;

private:
	CTimerInfo * FindTimerInfo(int nTimerId);

private:
	IOS &m_ios;
	typedef std::map<int, CTimerInfo *> MapTimerInfo;
	MapTimerInfo m_mapTimerInfo;
};

NS_LIB_FOOTER;

#endif