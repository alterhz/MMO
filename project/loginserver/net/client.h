//----------------------------------------
// 创建时间 : 2014-12-25
// 作者 : hanzhe
// 说明 : 客户端通信对象

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "asioinc.h"

class CClient : public ITcpSocket
{
public:
	CClient();

protected:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();
};

#endif