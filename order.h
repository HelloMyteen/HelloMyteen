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
	//����ͨ��ִ�ж���
	std::string getOperteName();
	Vec2 getOpertePos();
	void setOpName(std::string name);
	void setOpPos(Vec2 pos);

	//����Ϊ���������
	std::vector<Player>_players;
	int socketflag = 0;                 //�жϷ���˻��ǿͻ���
	SocketClient * _client = new SocketClient();
	SocketServer * _server = SocketServer::create();
	const char * ip = nullptr;
	Scene * _scene = nullptr;
	MapScene * _mapscene = nullptr;

	//����
	std::list<introduct>_orderlist;
	//��ͼѡ��
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

