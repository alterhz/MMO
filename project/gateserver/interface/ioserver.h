//----------------------------------------
// 创建时间 : 2014-11-13
// 作者 : hanzhe
// 说明 : 

#ifndef _IIOSERVICE_H_
#define _IIOSERVICE_H_

#include "interfacenet.h"
#include "header.h"

class CIOServer : public IIOServer
{
public:
	CIOServer();
	virtual ~CIOServer();

	// 启动
	virtual bool Start(IIOServerCallback *pIOServerCallBack);
	// 阻塞
	virtual void Run();
	// 非阻塞
	virtual void Poll();
	// 停止
	virtual bool Stop();
	// 异步事件
	virtual bool Post(ITask *pTask);

private:
	IIOServerCallback *m_pIOServerCallBack;
	boost::asio::io_service::work *m_pWork;
	boost::asio::io_service m_ios;
};

#endif