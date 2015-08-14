//============================
//���
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
	string name;                         //����

	vector<GameCard*> handCards;         //������
	GameCard *equipCards;                //װ����
	RoleCard *role;                      //��ɫ��
	vector<GameCard*> judgeCards;        //�ж���
	PowerCard *power;                    //������
};



#endif