//----------------------------------------
// ����ʱ�� : 2014-12-17
// ���� : hanzhe
// ˵�� : �ͻ���Acceptor

#ifndef _WANACCEPTOR_H_
#define _WANACCEPTOR_H_

#include "asioinc.h"

class CWanAcceptor : public ITcpAcceptor
{
public:
	CWanAcceptor(IOS &ios);
	~CWanAcceptor();

public:

protected:
	virtual ITcpSocket * OnAccept();
	virtual bool OnClose(ITcpSocket *pDelTcpSocket);

private:

};

#endif