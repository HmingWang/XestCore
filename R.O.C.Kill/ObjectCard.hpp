//=================================
//���ƻ���
//=================================

#ifndef _OBJECT_CARD_HPP_
#define _OBJECT_CARD_HPP_
#include <string>
using std::string;

class ObjectCard
{
public:
	string GetName();
	char Turnover();  //��ת����
private:
	string name;
	char face; //���泯��U��up��D��down��
	string exPackage; //��չ��
	string tips;//����˵��
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