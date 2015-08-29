#ifndef _ROLE_CARD_HPP_
#define _ROLE_CARD_HPP_

#include "ObjectCard.hpp"
#include "GameCard.hpp"

class RoleCard :public ObjectCard
{
public:
private:
	string party; //所属势力
	string power; //默认生命点数

};

#endif