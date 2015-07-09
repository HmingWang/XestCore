//============================
//���
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "stdxafx.h"

class Desktop;
class GameCard;
class RoleCard;
class PowerCard;
class ParserX;

class Player
{
public:
	Player(tcp::socket& socket,int id);
	~Player();
	string getAddress();
	void start();                       //��ʼ��Ϣѭ��
	string getMsg();
	void do_read();
	void do_write(string);
	int getId();
	
private:
	int id;                             //session id
	int index;                          //λ��
	vector<GameCard*> handCards;         //������
	GameCard *equipCards;               //װ����
	RoleCard *role;                      //��ɫ��
	vector<GameCard*> judgeCards;        //�ж���
	PowerCard *power;                    //������

	tcp::socket  socket;                //socket����
	queue<string> msgQueue;             //Message queue 
	boost::asio::streambuf wsbuf;       //д����Ϣ������//x
	boost::asio::streambuf rsbuf;       //��ȡ��Ϣ������
	string strbuff;                     //д����Ϣ������  
};



#endif