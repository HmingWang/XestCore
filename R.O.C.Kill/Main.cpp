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
#ifdef _WIN32
	cout << "_WIN32" << endl;
#endif
#ifdef WIN32
	cout << "WIN32" << endl;
#endif

	Server s;
	s.start();
	s.run();


#ifdef WIN32
	system("pause");
#endif

	return 0;
}