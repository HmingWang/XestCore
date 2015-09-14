#include "Server.hpp"

int main()
{


	cout << "系统环境：" << endl;
#ifdef __GNUC__
	cout << "__GNUC__" << endl;
#endif
#ifdef _MSC_VER
	cout << "_MSC_VER" << endl;
#endif

#ifdef WIN32
	//0 = 黑色       8 = 灰色
	//1 = 蓝色       9 = 淡蓝色
	//2 = 绿色       A = 淡绿色
	//3 = 浅绿色     B = 淡浅绿色
	//4 = 红色       C = 淡红色
	//5 = 紫色       D = 淡紫色
	//6 = 黄色       E = 淡黄色
	//7 = 白色       F = 亮白色

	system("color 0A");//黑绿
	system("color 1E");//蓝黄
	system("color 1F");//蓝白
#endif
	Server s;
	s.start();
	s.run();


#ifdef WIN32
	system("pause");
#endif

	return 0;
}