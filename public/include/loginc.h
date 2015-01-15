//----------------------------------------
// 创建时间 : 2015-1-4
// 作者 : hanzhe
// 说明 : Log

#ifndef _LOGINC_H_
#define _LOGINC_H_

#include "common/log.h"
#include "stringjoin.h"

extern NSLIB::Log *G_pLog;

typedef StringJoin<1024> TmpSJ;

// 错误
#define LogError(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("ERROR", tmpSJ.GetData());	\
	assert(0);	\
	}	\
}

// 警告
#define LogWarn(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("WARN", tmpSJ.GetData());	\
	}	\
}

// 信息
#define LogInfo(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("INFO", tmpSJ.GetData());	\
	}	\
}

// 调试
#define LogDebug(log) {	\
	TmpSJ tmpSJ;	\
	tmpSJ + log + "[" + __FILE__ + " - " + __LINE__ + "]";	\
	if (G_pLog)	{ \
	G_pLog->Write("DEBUG", tmpSJ.GetData());	\
	}	\
}

// 显示
#define PrintInConsole(text) { \
	TmpSJ tmpSJ;	\
	tmpSJ + text;	\
	std::cout << tmpSJ.GetData() << std::endl;	\
}

#endif