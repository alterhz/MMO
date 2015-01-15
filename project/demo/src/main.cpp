//----------------------------------------
// 创建时间 : 2014-12-4
// 作者 : hanzhe
// 说明 : main

#include "header.h"

#include <iostream>

void OnTimer(const boost::system::error_code& ec)
{
	if (ec)
	{
		if (ec.value() == boost::asio::error::operation_aborted)
		{
			std::cout << "boost::asio::error::operation_aborted" << std::endl;
		}
		else
		{
			std::cout << ec.message() << std::endl;
		}

		return ;
	}

	std::cout << "ontime" << std::endl;
}

boost::asio::io_service ios;

void OnThread()
{
	std::cout << "thread start." << std::endl;

	ios.run();

	std::cout << "thread finished." << std::endl;
}

void example1()
{
	boost::asio::deadline_timer dtimer(ios, boost::posix_time::millisec(10000));

	dtimer.async_wait(boost::bind(&OnTimer, boost::asio::placeholders::error));

	boost::thread t(boost::bind(&OnThread));
	t.detach();

	ios.stop();

	boost::this_thread::sleep(boost::posix_time::millisec(1000));
	dtimer.cancel();
}

void example2()
{
	boost::asio::io_service::work w(ios);

	boost::asio::deadline_timer dtimer(ios, boost::posix_time::millisec(1000));

	boost::this_thread::sleep(boost::posix_time::millisec(2000));

	dtimer.async_wait(boost::bind(&OnTimer, boost::asio::placeholders::error));

	//

	for (int i=0; i<10; ++i)
	{
		int n = ios.poll();

		std::cout << "n:" << n << std::endl;
	}



	ios.run_one();

	std::cout << "timer cancel." << std::endl;

	

	ios.run();

	//for(int i=0; i<10; ++i)
	//{
	//	ios.run_one();

	//	std::cout << "run_one" << std::endl;
	//}

	//ios.stop();

	boost::this_thread::sleep(boost::posix_time::millisec(1000));
	dtimer.cancel();
}
void OnConnect(const boost::system::error_code& ec)
{
	std::cout << "连接上" << std::endl;
}
void asioExample1()
{
	boost::asio::io_service::work w(ios);

	boost::asio::ip::tcp::socket sock(ios);

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8880);

	sock.async_connect(ep, 
		bind(&OnConnect, boost::asio::placeholders::error));

	char sz[32] = "hello world";
	//sock.send(boost::asio::buffer(sz));

	ios.run();
}



int main(int argc, const char *argv[])
{
	// 案例1
	//example1();	
	//example2();
	asioExample1();

	while(true)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(1000));
		//std::cout << "sleep 1000ms" << std::endl;
	}

	return 0;
}