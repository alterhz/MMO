//----------------------------------------
// 创建时间 : 2014-10-31
// 作者 : hanzhe
// 说明 : 

#ifndef _HEADER_H_
#define _HEADER_H_

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

#define LogError(log) {	\
	std::cout << log << "[" << __FILE__ << " - " << __LINE__ << "]" << std::endl;	\
}


#endif