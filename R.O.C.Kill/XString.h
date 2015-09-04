#ifndef _X_STRING_H_
#define _X_STRING_H_
#include <string>

class XString
{
private:
	std::string m_StringData;
	unsigned long m_StringLength;
public:
	XString() :m_StringData(""), m_StringLength(0){}
	unsigned long GetLength() { return m_StringLength; }
};


#endif
