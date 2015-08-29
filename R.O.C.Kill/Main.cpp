#include "Server.hpp"

int main()
{
	Server s;
	try
	{
		s.start();
		s.run();
	}

	catch (std::string &e)
	{
		cout << e << endl;
	}


	system("pause");
	return 0;
}