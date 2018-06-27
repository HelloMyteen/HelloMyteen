#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "MapScene.h"
#include "MyScene.h"
#include "SelectManager.h"
#include "cocos2d.h"
#include "string.h"
#include "Room.h"
#include "order.h"
#include "Player.h"
#include "Clientin.h"

USING_NS_CC;

extern Message message;
//**************************************************************   以下Room协议执行函数
bool execute(std::string allorder)      //Room协议执行函数
{
	std::size_t found = allorder.find("a!dd");
	std::string username;
	std::size_t leng = allorder.length();
	if (found < leng)
	{
		int judge = 0;
		Player _player;
		username = allorder.substr(0, found);
		_player.name = username;
		_player.flag = 4;
		for (auto x : message._players)
		{
			if (x.name == username)
			{
				judge++;
			}
		}
		if (judge == 0)
		{
			message._players.push_back(_player);
		}
	}
	std::size_t found1 = allorder.find("rea!dy");
	std::string username1;
	std::size_t leng1 = allorder.length();
	if (found1 < leng1)
	{
		int i = 0;
		username1 = allorder.substr(0, found1);
		for (auto x : message._players)
		{
			if (message._players[i].name==username1)
			{
				message._players[i].setready();
			}
			i++;
		}
	}
	return true;
}
//**************************************************************   以下回调函数
void onserverstart(const char* ip)
{
	message.ip = ip;
}
void onservernewcon(HSocket socket)
{
	std::string mynameadd;
	mynameadd = message._players[0].name + "a!dd";
	int leng = mynameadd.length();
	message._server->sendMessage(socket, mynameadd.c_str(), leng);
}
void onserverrecv(const char* data, int count)
{
	execute(data);
	message._server->sendMessage(data, count);
}
void onclientrecv(const char* data, int count)
{
	execute(data);
}
//*************************************************************    以下场景
Scene* Room::createScene()
{
	auto scene = Scene::create();
	auto layer = Room::create();
	scene->addChild(layer);
	message._scene = scene;
	return scene;
}
bool Room::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto menu = Sprite::create("black.png");
	menu->setPosition(size.width / 2, size.height / 2);
	menu->setScale(1.0f);
	this->addChild(menu);

	//  添加经过九宫格算法处理后的背景

	auto backgroundSelectManager = NinePatch3::createPatch(size.width, size.height, 0, Vec2(0, 0));
	addChild(backgroundSelectManager);

	auto pMapOne = MenuItemImage::create("START.png", "START.png", this, menu_selector(Room::BackToSelectManager));
	auto MapOne = Menu::create(pMapOne, NULL);
	MapOne->setAnchorPoint(Vec2(0, 0));
	MapOne->setPosition(size.width /2, size.height/16);
	MapOne->setScale(0.6f);
	this->addChild(MapOne);
	//可定义一张刷新图片




	//实现连接
	if (message._players[0].flag == 1)
	{
		message._server->onStart = onserverstart;
		message._server->onRecv = onserverrecv;
		message._server->onNewConnection = onservernewcon;
		message._server->startServer();
		auto* label = Label::create("This is your ip address", "fonts/cute.ttf", 20);
		label->setPosition(480, 600);
		label->setTextColor(Color4B(255, 0, 0, 255));
		this->addChild(label);
		auto* label1 = Label::create(message.ip, "fonts/cute.ttf", 20);
		label1->setPosition(480, 550);
		label1->setTextColor(Color4B(255, 0, 0, 255));
		this->addChild(label1);
	}
	else if (message._players[0].flag == 0)
	{
		std::string useradd;
		useradd = message._players[0].name + "a!dd";
		int leng = useradd.length();
		message._players[0].name.c_str();
		message._client->onRecv = onclientrecv;
		message._client->connectServer(message.ip, 8000);
		message._client->sendMessage(useradd.c_str(),leng);
	}
	//***************************以上，建立完连接，下方开始在房间载入玩家******************//
	scheduleUpdate();        //执行定时器，在数据传输时，实时刷新，获取更新信息
	schedule(schedule_selector(Room::myupdate), 0.1);       //
	return true;
}

void Room::BackToSelectManager(Ref* pSender)
{
	int i = 0, total = 0;
	message._players[0].setready();
	if (message._players[0].flag == 1)
	{
		std::string userrea;
		userrea = message._players[0].name + "rea!dy";
		int leng = userrea.length();
		message._server->sendMessage(userrea.c_str(),leng);
	}
	else
	{
		std::string userrea;
		userrea = message._players[0].name + "rea!dy";
		int leng = userrea.length();
		message._client->sendMessage(userrea.c_str(), leng);
	}
	for (auto x : message._players)
	{
		if (x.getready() == true)
			i++;
		total++;
	}
	if (total == i)
	{
		unscheduleUpdate();
		Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MapScene::createScene()));
	}
}

void Room::update(float dt)
{
	int i = 0;
	for (auto x : message._players)
	{
		if (i == 0)
		{
			if (message._players[i].labelflag == false)
			{
				auto* label0 = Label::create(message._players[i].name.c_str(), "fonts/cute.ttf", 30);
				label0->setPosition(220, 440);
				label0->setTextColor(Color4B(255, 255, 0, 255));
				this->addChild(label0);
				message._players[0].labelflag = true;
			}
			if (message._players[i].getready())
			{
				if (message._players[i].readyflag == false)
				{
					auto* label00 = Label::create("ready!", "fonts/cute.ttf", 30);
					label00->setPosition(220, 400);
					label00->setTextColor(Color4B(255, 255, 0, 255));
					this->addChild(label00);
					message._players[i].readyflag = true;
				}
			}
		}
		else if (i == 1)
		{
			if (message._players[i].labelflag == false)
			{
				auto* label1 = Label::create(message._players[i].name.c_str(), "fonts/cute.ttf", 30);
				label1->setPosition(740, 440);
				label1->setTextColor(Color4B(255, 255, 0, 255));
				this->addChild(label1);
				message._players[i].labelflag = true;
			}
			if (message._players[i].getready())
			{
				if (message._players[i].readyflag == false)
				{
					auto* label11 = Label::create("ready!", "fonts/cute.ttf", 30);
					label11->setPosition(740, 400);
					label11->setTextColor(Color4B(255, 255, 0, 255));
					this->addChild(label11);
					message._players[i].readyflag = true;
				}
			}
		}
		else if (i == 2)
		{
			if (message._players[i].labelflag == false)
			{

				auto* label2 = Label::create(message._players[i].name.c_str(), "fonts/cute.ttf", 30);
				label2->setPosition(220, 240);
				label2->setTextColor(Color4B(255, 255, 0, 255));
				this->addChild(label2);
				message._players[i].labelflag = true;
			}
			if (message._players[i].getready())
			{
				if (message._players[i].readyflag == false)
				{
					auto* label22 = Label::create("ready!", "fonts/cute.ttf", 30);
					label22->setPosition(220, 200);
					label22->setTextColor(Color4B(255, 255, 0, 255));
					this->addChild(label22);
					message._players[i].readyflag = true;
				}
			}
		}
		else if(i==3)
		{
			if (message._players[i].labelflag == false)
			{
				auto* label3 = Label::create(message._players[i].name.c_str(), "fonts/cute.ttf", 30);
				label3->setPosition(740, 240);
				label3->setTextColor(Color4B(255, 255, 0, 255));
				this->addChild(label3);
				message._players[i].labelflag = true;
			}
			if (message._players[i].getready())
			{
				if (message._players[i].readyflag == false)
				{
					auto* label33 = Label::create("ready!", "fonts/cute.ttf", 30);
					label33->setPosition(740, 200);
					label33->setTextColor(Color4B(255, 255, 0, 255));
					this->addChild(label33);
					message._players[i].readyflag = true;
				}
			}
		}
		i++;
	}
}

void Room::myupdate(float dt)
{
	int i = 0;
	int total = 0;
	for (auto x : message._players)
	{
		if (x.getready())
		{
			i++;
		}
		total++;
	}
	if (total == i)
	{
		Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MapScene::createScene()));
		unschedule(schedule_selector(Room::myupdate));
	}
}
