//----------------------------------------
// ����ʱ�� : 2014-12-25
// ���� : hanzhe
// ˵�� : �ͻ���ͨ�Ŷ���

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "asioinc.h"

enum EClientStatus
{
	EStatus_NotLoginIn = 0,	//δ��½
	EStatus_HaveLoginIn,	//�ѵ�½
};

class CClient : public ITcpSocket
{
public:
	CClient();
	~CClient() {}

	// �л�״̬
	void ChangeClientStatus(EClientStatus eClientStatus) { m_eClientStatus = eClientStatus; }

protected:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();

private:
	// δ��½���߼��ַ�
	void OnNotLoginInLogicDispatch(unsigned short wMsgId, const void *pProtoData, int nProtoLength);
	// �ѵ�¼���߼��ַ�
	void OnHaveLoginInLogicDispatch(unsigned short wMsgId, const void *pProtoData, int nProtoLength);

private:
	EClientStatus m_eClientStatus;
};

#endif