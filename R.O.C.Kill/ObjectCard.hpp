//=================================
//卡牌基类
//=================================

#ifndef _OBJECT_CARD_HPP_
#define _OBJECT_CARD_HPP_
#include <string>
using std::string;

class ObjectCard
{
public:
	string GetName();
	char Turnover();  //翻转牌面
private:
	string name;
	char face; //牌面朝向U（up）D（down）
	string exPackage; //扩展包
	string tips;//卡牌说明
};

string ObjectCard::GetName()
{
	return name;
}

char ObjectCard::Turnover()
{
	if (face == 'U')
		face = 'D';
	else
		face = 'U';
	return face;
}

#endif