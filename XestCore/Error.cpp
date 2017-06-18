#include "Error.h"

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <cstdarg>

void XestCore::Assert(char const * file, int line, char const * function, char const * message)
{
	fprintf(stderr, "\n%s:%i in %s ASSERTION FAILED:\n  %s\n",
		file, line, function, message);
	*((volatile int*)NULL) = 0;
	exit(1);
}

void XestCore::Assert(char const * file, int line, char const * function, char const * message, char const * format, ...)
{
	va_list args;
	va_start(args, format);

	fprintf(stderr, "\n%s:%i in %s ASSERTION FAILED:\n  %s ", file, line, function, message);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	fflush(stderr);

	va_end(args);
	*((volatile int*)NULL) = 0;
	exit(1);
}
