#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id,string name) : sessionId(id),name(name){
	std::cout << "[PLAY][ID: "<< sessionId <<"]" << "������ɫ ����["<<name<<"]" << std::endl;
}
Player::~Player(){
	std::cout << "[PLAY][ID: " << sessionId << "]" << "ע����ɫ ����[" << name << "]" << std::endl;
}



Session& Player::getSession(){
	return sSessionMgr.getSessionByID(sessionId);
}

int Player::getID()
{
	return sessionId;
}
