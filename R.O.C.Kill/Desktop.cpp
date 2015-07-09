#include"Desktop.h"
#include "Player.h"

void Desktop::join(sptr_player p)
{
	players.insert(p);
	//std::cout << "[进入房间]:" << p->getAddress() << std::endl;
	std::cout << "[当前人数]:" << players.size() << std::endl;
}
void Desktop::leave(sptr_player p){
	//std::cout << "[离开房间]:" << p->getAddress() << std::endl;
	players.erase(p);
	std::cout << "[当前人数]:" << players.size() << std::endl;
}
void Desktop::deliver(string msg){
	for (auto p : players){
		p->do_write(msg);
	}
}
sptr_player Desktop::getPlayerById(int id){
	for (auto p:players)
	{
		if (p->getId()==id)
		{
			return p;
		}
	}
	return nullptr;
}