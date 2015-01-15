//----------------------------------------
// ����ʱ�� : 2014-12-17
// ���� : hanzhe
// ˵�� : 

#ifndef _WANSOCKET_H_
#define _WANSOCKET_H_

#include "asioinc.h"

class CWanSocket : public ITcpSocket
{
public:
	CWanSocket();
	~CWanSocket();

protected:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();

};

#endif