//============================
//玩家
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
	void start();                       //开始消息循环
	string getMsg();
	void do_read();
	void do_write(string);
	int getId();
	
private:
	int id;                             //session id
	int index;                          //位序
	vector<GameCard*> handCards;         //手牌区
	GameCard *equipCards;               //装备区
	RoleCard *role;                      //角色牌
	vector<GameCard*> judgeCards;        //判定区
	PowerCard *power;                    //体力牌

	tcp::socket  socket;                //socket连接
	queue<string> msgQueue;             //Message queue 
	boost::asio::streambuf wsbuf;       //写入消息缓冲区//x
	boost::asio::streambuf rsbuf;       //读取消息缓冲区
	string strbuff;                     //写入消息缓冲区  
};



#endif