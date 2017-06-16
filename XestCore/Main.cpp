#include <iostream>
#include "Log.h"
#include "Socket.h"
#include "AsyncAcceptor.h"
#include "Session.h"
#include "SessionMgr.h"
#include "CompilerDefs.h"
using namespace std;

#define MODECODE "MAIN" 

//函数声明
void SignalHandler(boost::asio::io_service* ioServiceRef, boost::system::error_code const& error, int /*signalNumber*/);


int main()
{


	//0 = 黑色       8 = 灰色
	//1 = 蓝色       9 = 淡蓝色
	//2 = 绿色       A = 淡绿色
	//3 = 浅绿色     B = 淡浅绿色
	//4 = 红色       C = 淡红色
	//5 = 紫色       D = 淡紫色
	//6 = 黄色       E = 淡黄色
	//7 = 白色       F = 亮白色

	//system("color 0A");//黑绿
	//system("color 1E");//蓝黄

#if PLATFORM == PLATFORM_WINDOWS
	system("color 1F");//蓝白
#endif

	boost::asio::io_service ios;
	string ipAddr = "0.0.0.0";
	uint16 port = 1986;
	Trace("服务器启动：[IP:%s][Port:%d]  <Ctrl-C>停止服务", ipAddr.c_str(), port);

	if (!sSessionMgr.StartNetwork(ios, ipAddr, port, 2))
	{
		Trace("初始化网络服务失败");
		return 1;
	}

	//中断信号处理
	boost::asio::signal_set signals(ios, SIGINT, SIGTERM);
#if PLATFORM == PLATFORM_WINDOWS
	signals.add(SIGBREAK);
#endif
	signals.async_wait(std::bind(&SignalHandler, &ios, std::placeholders::_1, std::placeholders::_2));

	ios.run();

	Trace("服务器停止...");

	signals.cancel();

#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}

void SignalHandler(boost::asio::io_service* ioServiceRef, boost::system::error_code const& error, int /*signalNumber*/)
{
	Trace("接到中断信号");
	if (!error)
		ioServiceRef->stop();
}