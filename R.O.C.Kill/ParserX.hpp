#ifndef _PARSER_HPP_
#define _PARSER_HPP_
#include "stdxafx.h"
#include "Desktop.h"
#include "Player.h"
#include "Command.hpp"

class ParserX{
private:
	ParserX() = default;
	sptr_Desktop spDesktop;
	sptr_Player  spPlayer;
public:
	static ParserX& getInstance(){
		static ParserX instance;
		return instance;
	}
	void parserCommand(Command cmd){
		if (spDesktop == nullptr) {
			spDesktop = make_shared<Desktop>();
			cout << "[PARX]创建房间" << endl;
		}
		vector<String> argVec;
		argVec = cmd.GetMessage().Split(":");
		String msgBack = "OK";
		switch (atoi(argVec.front().c_str()))
		{
		case CMD_ECHO:
			sSessionMgr.SendTo(cmd.GetSessionID(), cmd.GetMessage());
			break;
		case CMD_KEEPALIVE:
			//通讯保持-业务确认
			break;
		case CMD_LOGIN:
			//登陆报文
			break;
		case CMD_CHAT:
			//聊天
			spDesktop->deliver(argVec.back());
			break;
		case CMD_CRTPLAYER:
			argVec = argVec.back().Split(";");
			spPlayer = make_shared<Player>(cmd.GetSessionID(), argVec.front(),argVec.back().compare("True")==0);
			spDesktop->join(cmd.GetSessionID(),spPlayer);
			break;
		case CMD_CRTDESKTOP:
			break;
		case CMD_REFRESH:
			spDesktop->refrash();
		default:
			sSessionMgr.SendTo(cmd.GetSessionID(), cmd.GetMessage());
			break;
		}
		//return std::move(msgBack);
	}
	void setDesktop(shared_ptr<Desktop> p){
		spDesktop = p;
	}
};

#define sParserX ParserX::getInstance()

#endif