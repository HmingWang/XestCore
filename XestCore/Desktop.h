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
	void join(int,sptr_Player);
	void leave(int);
	void deliver(string msg,int id=0);     //��ָ��ID������Ϣ��ID=0ʱ�㲥
	void refrash();                        //ˢ�·���״̬��Ϊÿ��ID���͵�ǰ����������
	Player& getPlayerById(int id);
private:
	map<int,sptr_Player> playerMap; //
	int max_players; //�������

};


typedef shared_ptr<Desktop> sptr_Desktop;


#endif