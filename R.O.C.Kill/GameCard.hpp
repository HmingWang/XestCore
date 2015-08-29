#ifndef _GAME_CARD_HPP_
#define _GAME_CARD_HPP_

#include"ObjectCard.hpp"

class GameCard :public ObjectCard
{
private:
	char rank;//����AKQJ2-10
	char suit;//��ɫ:�ں�÷��Spade Heart Club Diamond
	char type;//���ͣ����ҡ�������װ����ս������
public:
	char GetRank();
	char GetSuit();
	char GetType();
};

#endif