//---------------------------------------------------------------------
// author: alterhz
// created: 2015-1-20 23:26
// descript: 


#ifndef _WORLDCONNECTOR_H_
#define _WORLDCONNECTOR_H_

#include "asioinc.h"
#include "utility.h"
#include "protoinc.h"

class CWorldConnector : public ITcpConnector
{
public:
	CWorldConnector(IOS &ios);
	~CWorldConnector() {}

public:
	bool SendAccountLogin(const char *pAccount);

	bool SendProtoData(unsigned short wMsgId, const void *pProtoData, int nProtoLength);
	
private:
	bool Send(unsigned short wMsgId, google::protobuf::Message *pMessage);

public:
	virtual void OnEstablish();
	virtual void OnError(int nErrorCode);
	virtual bool OnRecvPacket(const char *pPacket, int nLength);
	virtual void OnTerminate();

};

#endif