//==================================
//����
//==================================

#ifndef _DESSKTOP_H_
#define _DESSKTOP_H_

#include "stdxafx.h"
#include "Player.h"


class Desktop
{
public:
	void join(sptr_Player);
	void leave(sptr_Player);
	void deliver(string);
	sptr_Player getPlayerById(int id);
private:
	std::set<sptr_Player> players; //
	int max_players; //�������

};


typedef shared_ptr<Desktop> sptr_Desktop;


#endif