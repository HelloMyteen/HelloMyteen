#pragma once

#include <string>
#include "Moveable.h"
#include "Player.h"
#include "SocketClient.h"
#include "SocketServer.h"
#include "MapScene.h"
#include "introduct.h"

class Message
{
public:
	Message() = default;
	void clean();

	std::string getOrder();
	std::string getPlayerOne();
	std::string getPlayerTwo();
	Moveable* getTargetOne();
	Moveable* getTargetTwo();

	void setOrder(const std::string str);
	void setPlayerOne(const std::string str);
	void setPlayerTwo(const std::string str);
	void setTargetOne( Moveable* unit);
	void setTargetTwo( Moveable* unit);
	//网络通信执行动作
	std::string getOperteName();
	Vec2 getOpertePos();
	void setOpName(std::string name);
	void setOpPos(Vec2 pos);

	//以下为网络库需求
	std::vector<Player>_players;
	int socketflag = 0;                 //判断服务端还是客户端
	SocketClient * _client = new SocketClient();
	SocketServer * _server = SocketServer::create();
	const char * ip = nullptr;
	Scene * _scene = nullptr;
	MapScene * _mapscene = nullptr;

	//尝试
	std::list<introduct>_orderlist;
	//地图选择
	int mapindex = 0;

private:
	std::string operatename;
	Vec2 operateposition;

	std::string order;

	std::string player1;
	Moveable* target1;
	std::string player2;
	Moveable* target2;
};

