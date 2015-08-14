#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id) : sessionId(id){
	std::cout << "[PLAY][ID: "<<id<<"]" << "创建角色" << std::endl;
}
Player::~Player(){
	std::cout << "[PLAY][ID: " << sessionId << "]" << "注销角色" << std::endl;
}



Session& Player::getSession(){
	return sSessionMgr.getSessionByID(sessionId);
}