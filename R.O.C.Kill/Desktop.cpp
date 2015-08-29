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
			if(p.second->getSession()->isConnected())
				p.second->getSession()->do_write(msg);
		}
	}
	else {
		if (playerMap[id]->getSession()->isConnected())
			playerMap[id]->getSession()->do_write(msg);
	}
}

void Desktop::refrash()
{
	string cmd = String().FromInt(PUSH_PLAYER) + ":";
	for (auto m : playerMap)
	{
		cmd += m.second->getName() + "," + m.second->getSex() + ";";
	}
	deliver(cmd);
}

sptr_Player Desktop::getPlayerById(int id){
	for (auto p: playerMap)
	{
		if (p.second->getID()==id)
		{
			return p.second;
		}
	}
	return nullptr;
}