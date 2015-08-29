#ifndef _GAME_CARD_HPP_
#define _GAME_CARD_HPP_

#include"ObjectCard.hpp"

class GameCard :public ObjectCard
{
private:
	char rank;//点数AKQJ2-10
	char suit;//花色:黑红梅方Spade Heart Club Diamond
	char type;//类型：锦囊、武器、装备、战马、宝物
public:
	char GetRank();
	char GetSuit();
	char GetType();
};

#endif