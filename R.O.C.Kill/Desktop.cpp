#include"Desktop.h"
#include "Player.h"

void Desktop::join(int id ,sptr_Player p)
{
	playerMap.insert(make_pair(id,p));
	std::cout << "[DESK][当前人数]:" << playerMap.size() << std::endl;
}
void Desktop::leave(int id){

	playerMap.erase(id);
	std::cout << "[DESK][当前人数]:" << playerMap.size() << std::endl;
}
void Desktop::deliver(string msg,int id){
	if (id == 0) {
		for (auto p : playerMap) {
			p.second->getSession().do_write(msg);
		}
	}
	else {
		playerMap[id]->getSession().do_write(msg);
	}
}

void Desktop::frash()
{

}

Player& Desktop::getPlayerById(int id){
	for (auto p: playerMap)
	{
		if (p.second->getID()==id)
		{
			return *p.second;
		}
	}
}