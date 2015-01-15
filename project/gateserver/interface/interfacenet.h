//----------------------------------------
// 创建时间 : 2014-12-1
// 作者 : hanzhe
// 说明 : 网络接口

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

class ITask
{
public:
	virtual ~ITask() {}

	virtual bool OnExcute() = 0;
};

class IIOServerCallback
{
public:
	virtual bool OnStop() = 0;
};

class IIOServer
{
public:
	IIOServer(){}
	virtual ~IIOServer() {}
	virtual bool Start(IIOServerCallback *pIOServerCallBack) = 0;
	virtual void Run() = 0;
	virtual void Poll() = 0;
	virtual bool Stop() = 0;
	virtual bool Post(ITask *pTask) = 0;
};


class ITcpSocketCallback
{
public:
	virtual bool OnConnect(bool bConnected) = 0;
	virtual bool OnRecv() = 0;
	virtual bool OnSend() = 0;
	virtual bool OnClose() = 0;
};

class ITcpSocket
{
public:
	ITcpSocket(){}
	virtual ~ITcpSocket(){}
	virtual bool BindIOServer(IIOServer * ios) = 0;
	virtual bool SetCallback(ITcpSocketCallback * cb) = 0;
	virtual bool DoConnect(const char *ip, unsigned short port) = 0;
	virtual bool DoSend(char * buf, unsigned int len) = 0;
	virtual bool DoRecv(char * buf, unsigned int len) =0;
	virtual bool GetPeerInfo(unsigned int * addr, unsigned short *port)=0;
	virtual bool Close() = 0;
};

class ITcpAcceptCallback
{
public:
	virtual bool OnAccept(ITcpSocket * s) = 0;
	virtual bool OnClose() = 0;
};

class ITcpAccept
{
public:
	ITcpAccept(){}
	virtual ~ITcpAccept(){}
	virtual bool BindIOServer(IIOServer * ios) = 0;
	virtual bool SetCallbck(ITcpAcceptCallback * cb) = 0;
	virtual bool OpenAccept(const char * ip, unsigned short port) = 0;
};

#endif