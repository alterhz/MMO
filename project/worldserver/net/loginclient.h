//----------------------------------------
// 创建时间 : 2015-1-10
// 作者 : hanzhe
// 说明 : 

#ifndef _LOGINCLIENT_H_
#define _LOGINCLIENT_H_

#include "asioinc.h"

class CLoginClient : public ITcpSocket
{
public:
	CLoginClient() {}
	~CLoginClient() {}

protected:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();
};

#endif