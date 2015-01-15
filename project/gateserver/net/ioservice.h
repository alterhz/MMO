//----------------------------------------
// 创建时间 : 2014-11-29
// 作者 : hanzhe
// 说明 : 

#ifndef _IOSERVICE_H_
#define _IOSERVICE_H_

#include "interfacenet.h"

typedef std::vector<ITcpSocket *> VtTcpAccept;

class CIOService : public IIOServerCallback
{
public:
	CIOService();
	~CIOService();

public:
	virtual void OnInitailize();
	virtual void OnRelease();

private:
	VtTcpAccept m_vtTcpAccept;
};

#endif