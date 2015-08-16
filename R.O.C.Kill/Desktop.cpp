#include"Desktop.h"
#include "Player.h"

void Desktop::join(sptr_Player p)
{
	players.insert(p);
	//std::cout << "[���뷿��]:" << p->getAddress() << std::endl;
	std::cout << "[DESK][��ǰ����]:" << players.size() << std::endl;
}
void Desktop::leave(sptr_Player p){
	//std::cout << "[�뿪����]:" << p->getAddress() << std::endl;
	players.erase(p);
	std::cout << "[DESK][��ǰ����]:" << players.size() << std::endl;
}
void Desktop::deliver(string msg){
	for (auto p : players){
		p->getSession().do_write(msg);
	}
}
sptr_Player Desktop::getPlayerById(int id){
	for (auto p:players)
	{
		if (p->getID()==id)
		{
			return p;
		}
	}
	return nullptr;
}