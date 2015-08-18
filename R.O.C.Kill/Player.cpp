#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id,string name,bool sex) : sessionId(id),name(name),sex(sex){
	string sextype = sex ? "[��]" : "[Ů]";
	std::cout << "[PLAY][ID: "<< sessionId <<"]" << "������ɫ ����["<<name<<"]"<< sextype << std::endl;
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
