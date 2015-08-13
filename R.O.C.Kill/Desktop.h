//==================================
//牌桌
//==================================

#ifndef _DESSKTOP_H_
#define _DESSKTOP_H_

#include "stdxafx.h"

class Player;

typedef std::shared_ptr<Player> sptr_player;

class Desktop
{
public:
	void join(sptr_player);
	void leave(sptr_player);
	void deliver(string);
	sptr_player getPlayerById(int id);
private:
	std::set<sptr_player> players; //
	int max_players; //最大人数

};





#endif