//============================
//玩家
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "stdxafx.h"
#include "Session.h"
#include "SessionMgr.hpp"

class Desktop;
class GameCard;
class RoleCard;
class PowerCard;
class ParserX;

class Player
{
public:
	Player(int sid);
	~Player();

	Session& getSession();
	
private:
	int sessionId;                       //Session id
	string name;                         //名称

	vector<GameCard*> handCards;         //手牌区
	GameCard *equipCards;                //装备区
	RoleCard *role;                      //角色牌
	vector<GameCard*> judgeCards;        //判定区
	PowerCard *power;                    //体力牌
};



#endif