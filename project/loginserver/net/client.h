//----------------------------------------
// 创建时间 : 2014-12-25
// 作者 : hanzhe
// 说明 : 客户端通信对象

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "asioinc.h"

enum EClientStatus
{
	EStatus_NotLoginIn = 0,	//未登陆
	EStatus_HaveLoginIn,	//已登陆
};

class CClient : public ITcpSocket
{
public:
	CClient();
	~CClient() {}

	// 切换状态
	void ChangeClientStatus(EClientStatus eClientStatus) { m_eClientStatus = eClientStatus; }

protected:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();

private:
	// 未登陆的逻辑分发
	void OnNotLoginInLogicDispatch(unsigned short wMsgId, const void *pProtoData, int nProtoLength);
	// 已登录的逻辑分发
	void OnHaveLoginInLogicDispatch(unsigned short wMsgId, const void *pProtoData, int nProtoLength);

private:
	EClientStatus m_eClientStatus;
};

#endif