#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id,string name,bool sex) : sessionId(id),name(name),sex(sex){
	string sextype = sex ? "[男]" : "[女]";
	std::cout << "[PLAY][ID: "<< sessionId <<"]" << "创建角色 名称["<<name<<"]"<< sextype << std::endl;
}
Player::~Player(){
	std::cout << "[PLAY][ID: " << sessionId << "]" << "注销角色 名称[" << name << "]" << std::endl;
}

sptr_Session Player::getSession(){
	return sSessionMgr.getSessionByID(sessionId);
}

int Player::getID()
{
	return sessionId;
}

string Player::getName()
{
	return this->name;
}

string Player::getSex()
{
	return this->sex ? "男" : "女";
}
