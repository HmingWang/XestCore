//==================================
//牌桌
//==================================

#ifndef _DESSKTOP_H_
#define _DESSKTOP_H_

#include "stdxafx.h"
#include "Player.h"


class Desktop
{
public:
	void join(int,sptr_Player);
	void leave(int);
	void deliver(string msg,int id=0);     //给指定ID发送消息，ID=0时广播
	void refrash();                        //刷新房间状态，为每个ID发送当前房间所有人
	Player& getPlayerById(int id);
private:
	map<int,sptr_Player> playerMap; //
	int max_players; //最大人数

};


typedef shared_ptr<Desktop> sptr_Desktop;


#endif