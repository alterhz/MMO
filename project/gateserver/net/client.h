//----------------------------------------
// ����ʱ�� : 2014-11-29
// ���� : hanzhe
// ˵�� : �ͻ���ͨ�Ŷ���

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "tcpsocket.h"

class CClient : public ITcpSocketCallback
{
public:
	CClient(CIOServer &ioService);
	~CClient();

public:
	virtual bool OnConnect(bool bConnected) { return true; }
	virtual bool OnRecv() { return true; }
	virtual bool OnSend() { return true; }
	virtual bool OnClose() { return true; }

private:
	virtual void OnEstablish() {}
	virtual void OnError(int nErrorCode) {}
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate() {}


private:
	ITcpSocket *m_pTcpSocket;
};

#endif