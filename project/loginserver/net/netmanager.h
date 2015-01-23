//---------------------------------------------------------------------
// author: alterhz
// created: 2015-1-23 23:10
// descript: 

#ifndef _NETMANAGER_H_
#define _NETMANAGER_H_

#include "utility.h"
#include "asioinc.h"

class CWorldConnector;

class CNetManager : public Singleton<CNetManager>
{
public:
	CNetManager();
	~CNetManager();

	bool InitNet(IOS *pIos);

	CWorldConnector * GetWorldConnector() { return m_pWorldConnector; }

private:
	IOS *m_pIos;
	CWorldConnector *m_pWorldConnector;
};


#endif