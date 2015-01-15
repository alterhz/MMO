//----------------------------------------
// ����ʱ�� : 2014-12-12
// ���� : hanzhe
// ˵�� : 

#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include "asioinc.h"

class CClientSocket : public ITcpSocket
{
public:
	CClientSocket();
	~CClientSocket();

public:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();

private:

};

#endif