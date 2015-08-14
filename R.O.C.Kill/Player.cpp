#include "Player.h"
#include "ParserX.hpp"

Player::Player(int id) : sessionId(id){
	std::cout << "[PLAY][ID: "<<id<<"]" << "������ɫ" << std::endl;
}
Player::~Player(){
	std::cout << "[PLAY][ID: " << sessionId << "]" << "ע����ɫ" << std::endl;
}



Session& Player::getSession(){
	return sSessionMgr.getSessionByID(sessionId);
}