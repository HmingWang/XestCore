#ifndef _ERROR_H_
#define _ERROR_H_

#include "CompilerDefs.h"

namespace XestCore
{
	void Assert(char const* file, int line, char const* function, char const* message);
	void Assert(char const* file, int line, char const* function, char const* message, char const* format, ...);
}

#if COMPILER == COMPILER_MICROSOFT
#define ASSERT_BEGIN __pragma(warning(push)) __pragma(warning(disable: 4127))
#define ASSERT_END __pragma(warning(pop))
#else
#define ASSERT_BEGIN
#define ASSERT_END
#endif

#define WPAssert(cond, ...) ASSERT_BEGIN do { if (!(cond)) XestCore::Assert(__FILE__, __LINE__, __FUNCTION__, #cond, ##__VA_ARGS__); } while(0) ASSERT_END

#define ASSERT WPAssert


#endif //_ERROR_H_
