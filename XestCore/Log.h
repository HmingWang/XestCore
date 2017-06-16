#ifndef _LOG_H_
#define _LOG_H_
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdarg.h>


class Log
{
private:
	Log()
	{
	}
public:
	static Log& GetInstance()
	{
		static Log logInstance;
		return logInstance;
	}


	void write(const char* strModeCode,const char* strMsg,...)
	{
		std::string strTime = GetSystemTime() + "[" + strModeCode + "]" + strMsg + '\n';
		va_list argList;
		va_start(argList, strMsg);
		vfprintf(stdout, strTime.c_str(), argList);
		va_end(argList);
	}

	std::string GetSystemTime()
	{
		auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "[%F %T]");
		return ss.str();
	}
};

#define sLog Log::GetInstance()
#define MODECODE "----"
#define Trace(...) sLog.write(MODECODE,__VA_ARGS__) 
#endif