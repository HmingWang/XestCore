#ifndef _XSTRING_HPP_
#define _XSTRING_HPP_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <limits>

#define XSTRING

class XString :public std::string
{
public:
	XString() :std::string(), Length(length()) {}
	XString(const char* str) :std::string(str), Length(length()) {}
	XString(std::string str) :std::string(str), Length(length()) {}
	XString(XString &str) :std::string(static_cast<std::string>(str)), Length(str.length()) {}
	XString &XString::operator=(const XString &str)
	{
		*static_cast<std::string*>(this) = str;
		return *static_cast<XString*>(this);
	}

	XString& Trim(std::string trimChars = " "){
		if (trimChars.empty()) trimChars=" ";
		return TrimHelper(trimChars,TrimBoth);
	}
	XString& TrimStart(std::string trimChars = " "){
		if (trimChars.empty()) trimChars = " ";
		return TrimHelper(trimChars, TrimHead);
	}
	XString& TrimEnd(std::string trimChars = " "){
		if (trimChars.empty()) trimChars = " ";
		return TrimHelper(trimChars, TrimTail);
	}
	XString& TrimHelper(std::string trimChars, int trimType){
		auto start=this->begin();
		auto end=this->end();
		std::string::iterator i;
	
		if (trimType != TrimTail) {
			for (start = this->begin(); start < this->end(); ++start) {
				for (i = trimChars.begin(); i < trimChars.end(); ++i) {
					if (*i == *start) break;
				}
				if (i == trimChars.end()) { // the character is not white space
					break;
				}
			}
		}

		if (trimType != TrimHead) {
			for (end = this->end(); end >= start; --end) {
				for (i = trimChars.begin(); i < trimChars.end(); ++i) {
					if (*i==*(end-1)) break;
				}
				if (i == trimChars.end()) { // the character is not white space
					break;
				}
			}
		}

		if (end != this->end())   this->erase(end, this->end());        //ÏÈÉ¾³ý½áÎ²
		if (start != this->begin()) this->erase(this->begin(), start);
		return *this;
	}
	std::vector<XString> Split(std::string separator,int count= std::numeric_limits<std::int32_t>::max()){
		std::vector<XString> strVec;
		std::string substr = *this;
		std::string strItem;
		long long  pos = 0;
		//while (separator.length()>0 && substr.find(separator)!=std::string::npos){    //if separator is a string use this 
		while (separator.length()>0&&count>0 && substr.find_first_of(separator)!=std::string::npos){
			//pos = substr.find(separator);
			pos = substr.find_first_of(separator);
			strItem = substr.substr(0, pos);
			substr = substr.substr(pos+separator.length());
			strVec.push_back(strItem);
			--count;
		}
		strVec.push_back(substr);
		return std::move(strVec);
	}

	static XString FromInt(int i) {
		return std::to_string(i);
	}

	template<typename Type>
	static XString ConvertFrom(Type type) 
	{
		std::stringstream ss;
		ss << type;
		return std::move(ss.str());
	}
	template<typename Type>
	Type ConvertTo() 
	{
		std::stringstream ss;
		Type type;
		ss << *this;
		ss >> type;
		return std::move(type);
	}

private:
	const int TrimHead = 0;
	const int TrimTail = 1;
	const int TrimBoth = 2;

	std::string m_strData;
	long long Length;

};


#endif