//----------------------------------------
// ����ʱ�� : 2014-10-31
// ���� : hanzhe
// ˵�� : 

#ifndef _BOOSTHEADER_H_
#define _BOOSTHEADER_H_

// boost������
#define BOOST_ALL_NO_LIB
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/timer.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/lexical_cast.hpp>

// ������
#include <iostream>

#ifdef WIN32
	#include <conio.h>
	#include <windows.h>
#else

#endif // WIN32


//#define LogError(log) {	\
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	\
//	SetConsoleTextAttribute(hConsole,  FOREGROUND_RED|FOREGROUND_INTENSITY);	\
//	std::cout << log << "[" << __FILE__ << " - " << __LINE__ << "]" << std::endl;	\
//}

//#define LogError(log) {	\
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	\
//	SetConsoleTextAttribute(hConsole,  FOREGROUND_RED|FOREGROUND_INTENSITY);	\
//}

// �ض���
typedef boost::asio::io_service IOS;

// ��������ռ����ƶ���
#define NS_LIB_HEADER	namespace HZCore{
#define NS_LIB_FOOTER	}
#define NSLIB	HZCore


#endif