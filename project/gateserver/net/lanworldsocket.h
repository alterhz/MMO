//----------------------------------------
// ����ʱ�� : 2014-12-18
// ���� : hanzhe
// ˵�� : 

#ifndef _LANWORLDSOCKET_H_
#define _LANWORLDSOCKET_H_

#include "asioinc.h"

class CLanWorldSocket : public ITcpConnector
{
public:
	CLanWorldSocket(IOS &ios);

public:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode) {}
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate() {}
};

#endif