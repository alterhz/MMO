//----------------------------------------
// ����ʱ�� : 2014-11-13
// ���� : hanzhe
// ˵�� : 

#ifndef _IIOSERVICE_H_
#define _IIOSERVICE_H_

#include "interfacenet.h"
#include "header.h"

class CIOServer : public IIOServer
{
public:
	CIOServer();
	virtual ~CIOServer();

	// ����
	virtual bool Start(IIOServerCallback *pIOServerCallBack);
	// ����
	virtual void Run();
	// ������
	virtual void Poll();
	// ֹͣ
	virtual bool Stop();
	// �첽�¼�
	virtual bool Post(ITask *pTask);

private:
	IIOServerCallback *m_pIOServerCallBack;
	boost::asio::io_service::work *m_pWork;
	boost::asio::io_service m_ios;
};

#endif