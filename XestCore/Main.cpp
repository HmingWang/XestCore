#include <iostream>
#include "Log.h"
#include "Socket.h"
#include "AsyncAcceptor.h"
#include "Session.h"
#include "SessionMgr.h"
using namespace std;

int main()
{

#ifdef WIN32
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
	system("color 1F");//蓝白
#endif

	boost::asio::io_service ios;
	string ipAddr = "0.0.0.0";
	uint16 port = 1986;
	Trace("[MAIN]服务器启动：[IP:%s][Port:%d]", ipAddr.c_str(), port);

	sSessionMgr.StartNetwork(ios, ipAddr, port, 1);

	ios.run();

	system("pause");
	return 0;
}