//----------------------------------------
// ����ʱ�� : 2015-1-10
// ���� : hanzhe
// ˵�� : Ӧ�ó�������

#ifndef _APP_H_
#define _APP_H_

#include "utility.h"

class CApp : public Singleton<CApp>
{
public:
	CApp();
	~CApp();

public:
	bool Init();
	void Release();

private:
	bool InitLog();
	bool InitRes();
	bool InitNet();

};

#endif