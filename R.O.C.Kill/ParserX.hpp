#ifndef _PARSER_HPP_
#define _PARSER_HPP_
#include "stdxafx.h"
#include "Desktop.h"
#include "Command.hpp"

class ParserX{
private:
	ParserX() = default;
	shared_ptr<Desktop> sptr_desktop;
public:
	static ParserX& getInstance(){
		static ParserX instance;
		return instance;
	}
	void parserCommand(Command cmd){
		if (sptr_desktop == nullptr) {
			cout << "变量未绑定：[Desktop]" << endl;
			return;
		}
		vector<String> argVec;
		argVec = cmd.cmdmsg.Split(":");
		String msgBack = "OK";
		switch (atoi(argVec.front().c_str()))
		{
		case CMD_KEEPALIVE:
			//通讯保持-业务确认
			break;
		case 102:
			//登陆报文
			break;
		case CMD_CHAT:
			//聊天
			//return "chat:" + argVec.back();
			sptr_desktop->deliver(argVec.back());
			break;
		case CMD_SETPLAY:

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