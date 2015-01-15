//----------------------------------------
// 创建时间 : 2014-12-12
// 作者 : hanzhe
// 说明 : 接收器

#ifndef _CLIENTACCEPTOR_H_
#define _CLIENTACCEPTOR_H_

#include "asioinc.h"

class CClientAcceptor : public ITcpAcceptor
{
public:
	CClientAcceptor(IOS &ios);
	~CClientAcceptor();

	void CloseTmpSocket();

protected:
	virtual ITcpSocket * OnAccept();

private:
	ITcpSocket *m_pTmpSocket;
};

#endif