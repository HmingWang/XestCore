//====================================================
//Standard Xest Application Framework Extensions
//
//Copyright Xest Studio.
//Date:     2015-01-01
//Author:   Xest
//Version:  0.0.1
//====================================================

#ifndef _STDXAFX_H_
#define _STDXAFX_H_

#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include "XString.hpp"

#define String XString
//#define String std::string 

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::queue;
using std::shared_ptr;
using std::make_shared;
using boost::asio::ip::tcp;

//�궨��
//��������
#define CMD_KEEPALIVE   101 
#define CMD_LOGIN       102
#define CMD_CHAT        103
#define CMD_SECRIT      104
#define CMD_CRTPLAYER   105
#define CMD_CRTDESKTOP  106

#endif //_STDXAFX_H_