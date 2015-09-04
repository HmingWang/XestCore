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
#include<exception>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include "XString.hpp"

#ifdef XSTRING
#define String XString
#else
#define String std::string 
#endif

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
using std::exception;
using boost::asio::ip::tcp;

//宏定义
//操作命令
#define CMD_ECHO        100
#define CMD_KEEPALIVE   101 
#define CMD_LOGIN       102
#define CMD_CHAT        103
#define CMD_SECRIT      104
#define CMD_CRTPLAYER   105
#define CMD_CRTDESKTOP  106
#define CMD_REFRESH     107
//推送
#define PUSH_PLAYER     201
#define PUSH_CHAT       202

//字符串常量
const string cstr_login = string(
	"\n====================================================\n") +
	"===        天下风云出我辈， 一入江湖岁月催；     ===\n" +
	"===        皇图霸业谈笑间， 不胜人生一场醉。     ===\n" +
	"===        提剑跨骑挥鬼雨， 白骨如山鸟惊飞；     ===\n" +
	"===        尘事如潮人如水， 只叹江湖几人回。     ===\n" +
	"====================================================\n";

#endif //_STDXAFX_H_