//----------------------------------------
// ����ʱ�� : 2015-1-4
// ���� : hanzhe
// ˵�� : Log

#ifndef _LOGINC_H_
#define _LOGINC_H_

#include "common/log.h"
#include "stringjoin.h"

extern NSLIB::Log *G_pLog;

typedef StringJoin<1024> TmpSJ;

// ����
#define LogError(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("ERROR", tmpSJ.GetData());	\
	assert(0);	\
	}	\
}

// ����
#define LogWarn(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("WARN", tmpSJ.GetData());	\
	}	\
}

// ��Ϣ
#define LogInfo(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("INFO", tmpSJ.GetData());	\
	}	\
}

// ����
#define LogDebug(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("DEBUG", tmpSJ.GetData());	\
	}	\
}

// ��ʾ
#define PrintInConsole(text) { \
	TmpSJ tmpSJ;	\
	tmpSJ + text;	\
	std::cout << tmpSJ.GetData() << std::endl;	\
}

#endif