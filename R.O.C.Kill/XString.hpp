#ifndef _CSTRING_HPP_
#define _CSTRING_HPP_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class XString :public std::string
{
public:
	XString():std::string(),Length(length()){}
	XString(const char* str) :std::string(str), Length(length()){}
	XString(std::string str) :std::string(str), Length(length()){}

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
	std::vector<XString> Split(std::string separator,int count=INT_MAX){
		std::vector<XString> strVec;
		std::string substr = *this;
		std::string strItem;
		int pos = 0;
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

	XString FromInt(int i) {
		std::stringstream ss;
		ss << i;
		return ss.str();
	}


private:
	const int TrimHead = 0;
	const int TrimTail = 1;
	const int TrimBoth = 2;

	std::string m_strData;
	int Length;

};


#endif