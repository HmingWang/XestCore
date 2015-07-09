#ifndef _POWER_CARD_
#define _POWER_CARD_

#include"ObjectCard.hpp"

class PowerCard :public ObjectCard
{
private:
	int point;//Power Point 
public:
	int GetPoint();
	int Increase(int); //increase point
	int Decrease(int); //decrease point
};

#endif