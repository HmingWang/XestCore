#include <iostream>
#include "Log.h"

using namespace std;

int main()
{
    sLog->Initialize(nullptr);
    TC_LOG_INFO("server","Server is Starting...");

    return 0;
}

