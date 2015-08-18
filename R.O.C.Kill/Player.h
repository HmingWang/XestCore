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
	Player(int sid,string name,bool sex=true);
	~Player();

	Session& getSession();
	int getID();
	
private:
	int sessionId;                       //Session id
	string name;                         //����
	bool sex;                            //�Ա�  true :man  false: woman

	vector<GameCard*> handCards;         //������
	GameCard *equipCards;                //װ����
	RoleCard *role;                      //��ɫ��
	vector<GameCard*> judgeCards;        //�ж���
	PowerCard *power;                    //������
};

typedef shared_ptr<Player> sptr_Player;

#endif