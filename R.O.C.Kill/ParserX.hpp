#ifndef _PARSER_HPP_
#define _PARSER_HPP_
#include "stdxafx.h"
#include "Desktop.h"

class ParserX{
private:
	ParserX() = default;
	shared_ptr<Desktop> sptr_desktop;
public:
	static ParserX& getInstance(){
		static ParserX instance;
		return instance;
	}
	void parserCommand(String s){
		if (sptr_desktop == nullptr) {
			cout << "����δ�󶨣�[Desktop]" << endl;
			return;
		}
		vector<String> argVec;
		argVec = s.Split(":");
		String msgBack = "OK";
		switch (atoi(argVec.front().c_str()))
		{
		case 101:
			//ͨѶ����-ҵ��ȷ��
			break;
		case 102:
			//��½����
			break;
		case 103:
			//����
			//return "chat:" + argVec.back();
			sptr_desktop->deliver(argVec.back());
			break;
		default:
			break;
		}
		//return std::move(msgBack);
	}
	void setDesktop(shared_ptr<Desktop> p){
		sptr_desktop = p;
	}
};

#define sParserX ParserX::getInstance()

#endif