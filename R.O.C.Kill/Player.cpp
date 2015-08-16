#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id,string name) : sessionId(id),name(name){
	std::cout << "[PLAY][ID: "<< sessionId <<"]" << "创建角色 名称["<<name<<"]" << std::endl;
}
Player::~Player(){
	std::cout << "[PLAY][ID: " << sessionId << "]" << "注销角色 名称[" << name << "]" << std::endl;
}



Session& Player::getSession(){
	return sSessionMgr.getSessionByID(sessionId);
}

int Player::getID()
{
	return sessionId;
}
