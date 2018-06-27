//
//  MapScene.cpp
//  firstcode-mobile
//
//  Created by 叶琪 on 2018/6/13.
//



#include "MapScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "Toast.h"
#include "Moveable.h"
#include "order.h"
#include "cocos2d.h"
#include "SelectManager.h"
#include <string>
#include <list>
//#include "Room.h"
//#include "MutiPlayerMapSelect.h"
//#include "extensions\cocos-ext.h"
//#include "Moveable.h"


//extern std::vector<Player> _players;
//extern int socketflag;
Message message;
USING_NS_CC;
//USING_NS_CC_EXT;
//*************************************************************** 以下为网络库需求
bool executeP(std::string orderp)
{
	//根据消息开头判定，是否是协议定义排序
	introduct order;
	std::size_t found = orderp.find("P/");
	if (found != std::string::npos)   //重新编序
	{
		int i = 0;
		for (auto x : message._players)
		{
			order._username ="-" + message._players[i].name;
			found = orderp.find(order._username);
			std::string index = orderp.substr(found - 1, 1);
			message._players[i].index = (int)atof(index.c_str());              /*****************************************************/
			i++;
		}
		return true;
	}
	//确定消息来自何方
	//确定消息模式
	//根据不同的模式传递不同的参数列表
	else
	{
		std::size_t foundB, foundE;
		std::size_t found1 = orderp.find("^");//创建判定，后跟随创建对象，12兵，13狗，11车，25车厂，24兵场，22矿场，23电厂
		std::size_t found2 = orderp.find("&");//攻击判定
		std::size_t found3 = orderp.find("*");//移动判定
		if (found1 != std::string::npos)     //创建
		{
			order.mode = 1;
			order._username = orderp.substr(0, found1);
			foundB = found1;
			foundE = orderp.find("(");
			std::string type1 = orderp.substr(foundB+1,foundE-foundB-1);
			order.attack = (int)atof(type1.c_str());
			foundB = foundE;
			foundE = orderp.find(",");
			std::string pox1 = orderp.substr(foundB + 1, foundE - foundB - 1);
			foundB = foundE;
			foundE = orderp.find(")");
			std::string poy1 = orderp.substr(foundB + 1, foundE - foundB - 1);
			foundB = foundE;
			foundE = orderp.find("%");
			std::string ta = orderp.substr(foundB + 1, foundE - foundB - 1);
			order.tage = (int)atof(ta.c_str());
			order.putposition.x = atof(pox1.c_str());
			order.putposition.y = atof(poy1.c_str());
			//获取完毕，下方为执行区，order._username为操作者，order.attack这里为创建类型，
			//if (order.attack < 14 && order.attack >= 11 && order._username != message._players[0].name)
			//{
			//	auto moves = Moveable::create("soldierleft.png");
			//	map->addChild(moves,20);
			//	moves->addMoveable(order.putposition, order.attack);
			//	moves->setTag(order.tage);
			//	message._mapscene->_moveablesE.push_back(moves);

			//	/*message.moveablesE[i]->addMoveable(order.putposition, order.attack);
			//	message.moveablesE[i]->setTag(order.tage);*/
			//}
			//else if (order.attack > 21 && order.attack < 26 && order._username != message._players[0].name)
			//{
			//	auto buildings = Building::create("base.png");
			//	map->addChild(buildings, 20);
			//	buildings->initBuilding(order.putposition, order.attack);
			//	buildings->setTag(order.tage);
			//	message._mapscene->_buildingsE.push_back(buildings);
			//	/*message.buildingsE[i]->initBuilding(order.putposition, order.attack);
			//	message.buildingsE[i]->setTag(order.tage);*/
			//}

		}
		else if (found2 != std::string::npos)     //攻击
		{
			order.mode = 2;
			order._username = orderp.substr(0, found2);
			foundB = found2;
			foundE = orderp.find(",");
			std::string target1 = orderp.substr(foundB + 1, foundE - foundB - 1);
			foundB = foundE;
			foundE = orderp.find("%");
			std::string target2 = orderp.substr(foundB + 1, foundE - foundB - 1);
			order.attack = (int)atof(target1.c_str());
			order.isattack = (int)atof(target2.c_str());
			//下方为执行
			/*auto targetone = (Moveable*)message._mapscene->getChildByTag(order.attack);
			auto targettwo = (Moveable*)message._mapscene->getChildByTag(order.isattack);
			targettwo->order.isattacked(targetone);*/
		}
		else if (found3 != std::string::npos)    //移动
		{
			order.mode = 3;
			order._username = orderp.substr(0, found3);
			foundB = found3;
			foundE = orderp.find("(");
			std::string type1 = orderp.substr(foundB + 1, foundE - foundB - 1);
			order.attack = (int)atof(type1.c_str());
			foundB = foundE;
			foundE = orderp.find(",");
			std::string pox3 = orderp.substr(foundB + 1, foundE - foundB - 1);
			foundB = foundE;
			foundE = orderp.find(")");
			std::string poy3 = orderp.substr(foundB + 1, foundE - foundB - 1);
			order.putposition.x = atof(pox3.c_str());
			order.putposition.y = atof(poy3.c_str());
			//此处order.attack为精灵编号，下方执行
			/*int i = 0;
			for (auto x:message._mapscene->_moveablesE)
			{
				if (x->getTag() == order.attack)
				{
					message._mapscene->_moveablesE[i]->moveMoveable(order.putposition);
					break;
				}
				i++;
			}*/
		}
		message._orderlist.push_back(order);
	}
	return true;
	//************************************************************
}

void onserverrecvP(const char* data, int count)
{
	executeP(data);
	message._server->sendMessage(data, count);
}
void onclientrecvP(const char* data, int count)
{
	executeP(data);
}
//*************************************************************** 以上为网络库需求
Scene* MapScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MapScene::create();
	if (!scene->initWithPhysics());
    scene->addChild(layer);
	message._mapscene = layer;
    return scene;
}

bool MapScene::init()
{
	if (message._players[0].flag == 1)
	{
		message._server->onRecv = onserverrecvP;
	}
	else
	{
		message._client->onRecv = onclientrecvP;
	}

	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();

	
	//    cocos2d::Size MapScene_Size(size.width/2,size.height);
	//    this->setContentSize(MapScene_Size);
	if (message.mapindex == 1)
	{
		map = TMXTiledMap::create("untitled.tmx");
		map->setAnchorPoint(Vec2(0, 0));
		map->setPosition(Vec2(0, 0));
	}
	else if(message.mapindex == 2)
	{
		map = TMXTiledMap::create("untitled2.tmx");
		map->setAnchorPoint(Vec2(0, 0));
		map->setPosition(Vec2(0, 0));
	}

	this->addChild(map, 0, 100);
	//发送消息  决定玩家顺序
	if (message._players[0].flag == 1)
	{
		message._players[0].index = 1;
		int i = 1;
		std::string nameindex="P/";
		for (auto x : message._players)
		{
			nameindex = nameindex + std::to_string(i) + "-" + x.name;
			message._players[i - 1].index = i;
			i++;
		}
		message._server->sendMessage(nameindex.c_str(), nameindex.length());
	}

	prebase();

	cocos2d::Size mapSize = map->getMapSize();

	auto* Menu = Sprite::create("Menu.png");
	Menu->setAnchorPoint(Vec2(1,1));
	Menu->setPosition(size.width, size.height);
	addChild(Menu);
	this->moneyboard = ScoreBroad::createScoreBroad(message._players[0].getMoney(), 50, 100, "money", 1, size.width / 2 + 340, size.height / 2 + 160);
	addChild(moneyboard);
	this->powerboard = ScoreBroad::createScoreBroad(message._players[0].getPower(), 50, 100, "power", 2, size.width / 2 + 415, size.height / 2 + 160);
	addChild(powerboard);
	/********************                   MINE              *********************************/
	auto mine = Sprite::create("buildingmine.png");
	mine->setPosition(size.width - 115, size.height / 2 + 70);
	mine->setScale(0.5f);
	mine->setTag(BUIDMINE_TYPE);
	this->addChild(mine, 4);

	//菜单栏上矿厂的监听器
	auto listenermine = EventListenerTouchOneByOne::create();
	listenermine->setSwallowTouches(true);
	listenermine->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			log("order is clean!");
			message.clean();
			message.setOrder("buildmine");
			log("mine in menu is touched! You will build a mine if you touch map");
			return true;
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenermine, mine);
	/***************************************************************************************/

	/********************                   BuildingCar              *********************************/
	auto buildingcar = Sprite::create("buildingcar.png");
	buildingcar->setPosition(size.width - 115, size.height / 2 + 20);
	buildingcar->setScale(0.5f);
	buildingcar->setTag(BUIDCAR_TYPE);
	this->addChild(buildingcar, 4);

	//菜单栏上车厂的监听器
	auto listenerbuildingcar = EventListenerTouchOneByOne::create();
	listenerbuildingcar->setSwallowTouches(true);
	listenerbuildingcar->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			log("order is clean!");
			message.clean();
			message.setOrder("buildBuildingcar");
			log("buildingcar in menu is touched! You will build a mine if you touch map");
			return true;
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingcar, buildingcar);
	/***************************************************************************************/

	/********************                   BuildingSoldier              *********************************/
	auto buildingsoldier = Sprite::create("buildingsoldier.png");
	buildingsoldier->setPosition(size.width - 115, size.height / 2 -30);
	buildingsoldier->setScale(0.5f);
	buildingsoldier->setTag(BUIDSOLDIER_TYPE);
	this->addChild(buildingsoldier, 4);

	//菜单栏上兵工厂的监听器
	auto listenerbuildingsoldier = EventListenerTouchOneByOne::create();
	listenerbuildingsoldier->setSwallowTouches(true);
	listenerbuildingsoldier->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			log("order is clean!");
			message.clean();
			message.setOrder("buildBuildingsoldier");
			log("buildingsoldier in menu is touched! You will build a mine if you touch map");
			return true;
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingsoldier, buildingsoldier);
	/***************************************************************************************/

	/********************                   BuildingPower              *********************************/
	auto buildingpower = Sprite::create("buildingpower.png");
	buildingpower->setPosition(size.width - 115, size.height / 2-80);
	buildingpower->setScale(0.5f);
	buildingpower->setTag(BUIDPOWER_TYPE);
	this->addChild(buildingpower, 4);

	//菜单栏上电厂的监听器
	auto listenerbuildingpower = EventListenerTouchOneByOne::create();
	listenerbuildingpower->setSwallowTouches(true);
	listenerbuildingpower->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			log("order is clean!");
			message.clean();
			message.setOrder("buildBuildingpower");
			log("buildingpower in menu is touched! You will build a mine if you touch map");
			return true;
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingpower, buildingpower);
	/***************************************************************************************/

	/***********************               SOLDIER          ********************************/
	auto soldier = Sprite::create("soldierleft.png");
	soldier->setPosition(size.width - 115, size.height / 2 -130);
	soldier->setScale(0.4f);
	soldier->setTag(BUIDSOLDIER_TYPE);
	this->addChild(soldier, 4);

	//菜单栏上大兵的监听器
	auto listenersoldier = EventListenerTouchOneByOne::create();
	listenersoldier->setSwallowTouches(true);
	listenersoldier->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			if (true)
				/* 这里判断是否存在兵营 */
			{
				log("order is clean!");
				auto toast = Toast::create(
					"soldier in menu is touched! You will build a soldier if you touch map", 15, 3);
				this->addChild(toast);
				message.clean();
				message.setOrder("buildsoldier");
				return true;
			}
			else
				/* 不存在应该给个弹窗提示无兵营不允许创建坦克 */
			{
				auto toast = Toast::create(
					"You don't have a SoldierFactory.", 20, 3);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenersoldier, soldier);
	/********************                  SOLDIER                 *****************************/

	auto listener = EventListenerTouchAllAtOnce::create();
	cocos2d::Point mappoint = map->convertToNodeSpace(map->getPosition());

	while (0 <= mappoint.y && mappoint.y <= (mapSize.height - size.height));
	{
	listener->onTouchesMoved = CC_CALLBACK_2(MapScene::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	mappoint = map->convertToNodeSpace(map->getPosition());
}
	auto listenermap = EventListenerTouchOneByOne::create();
	listenermap->onTouchBegan = [this](Touch * touch, Event* event)
	{
		log("map is touched!!!");
		


		EventTouch * e = (EventTouch *)event;
		Point point = touch->getLocation();

		log("%d,%d", point.x, point.y);

		if (message.getOrder() == "buildcar"&&message._players[0].getIsCarFactory())
		{
			if (message._players[0].getMoney()<TANK_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - TANK_PRICE);
			log("car was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			auto tank = Moveable::create("soldierleft.png");
			map->addChild(tank, 20);
			tank->addMoveable(putPosition, TANK_TYPE);
			auto physicsBodyD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyD->setGravityEnable(false);
			tank->addComponent(physicsBodyD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			tank->setblood(buildingblood);
			tank->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));
			_moveables.push_back(tank);
			int i = 0;
			for (auto x : _moveables)
			{
				if (x == tank)
				{
					_moveables[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^11" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")" + std::to_string(message._players[0].index * 1000 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(),mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}

			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the car is，%f,%f", putPosition.x, putPosition.y);
		}
		else if (message.getOrder() == "buildsoldier"&&message._players[0].getIsSoldierFactory())
		{
			if (message._players[0].getMoney()<SOLDIER_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - SOLDIER_PRICE);
			log("soldier was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			auto soldier = Moveable::create("soldierleft.png");
			map->addChild(soldier, 20);
			soldier->addMoveable(putPosition, BUIDSOLDIER_TYPE);
			auto physicsBodyD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyD->setGravityEnable(false);
			soldier->addComponent(physicsBodyD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			soldier->setblood(buildingblood);
			soldier->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));
			_moveables.push_back(soldier);
			int i = 0;
			for (auto x : _moveables)
			{
				if (x == soldier)
				{
					_moveables[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^12" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")"+std::to_string(message._players[0].index * 1000 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
						message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}
			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the soldier is，%f,%f", putPosition.x, putPosition.y);
		}
		else if (message.getOrder() == "buildmine"&&message._players[0].getIsBase())
		{
			if (message._players[0].getMoney()<BUIDMINE_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			else if (message._players[0].getPower()<BUIDMINE_POWER)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the power!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - BUIDMINE_PRICE);
			message._players[0].setPower(message._players[0].getPower() - BUIDMINE_POWER);
			log("mine was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			auto mine = Building::create("buildingmine.png");
			map->addChild(mine, 20);
			mine->initBuilding(putPosition, BUIDMINE_TYPE);
			auto physicsBodyFD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyFD->setGravityEnable(false);
			physicsBodyFD->setDynamic(false);
			mine->addComponent(physicsBodyFD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			mine->setblood(buildingblood);
			mine->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));
			_buildings.push_back(mine);
			int i = 0;
			for (auto x : _buildings)
			{
				if (x == mine)
				{
					_buildings[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^22" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")" + std::to_string(message._players[0].index * 1250 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}
			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the mine is，%f,%f", putPosition.x, putPosition.y);
		}
		else if (message.getOrder()._Equal("buildBuildingcar") && message._players[0].getIsBase())
		{
			if (message._players[0].getMoney()<BUIDCAR_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			else if (message._players[0].getPower()<BUIDCAR_POWER)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the power!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - BUIDCAR_PRICE);
			message._players[0].setPower(message._players[0].getPower() - BUIDCAR_POWER);
			log("buildingcar was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			auto buildingcar = Building::create("buildingcar.png");
			map->addChild(buildingcar, 20);
			buildingcar->initBuilding(putPosition, BUIDCAR_TYPE);
			auto physicsBodyFD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyFD->setGravityEnable(false);
			physicsBodyFD->setDynamic(false);
			buildingcar->addComponent(physicsBodyFD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			buildingcar->setblood(buildingblood);
			buildingcar->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));
			_buildings.push_back(buildingcar);
			int i = 0;
			for (auto x : _buildings)
			{
				if (x == buildingcar)
				{
					_buildings[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^25" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")" + std::to_string(message._players[0].index * 1250 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}
			

			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the buildingcar is，%f,%f", putPosition.x, putPosition.y);
		}
		else if (message.getOrder()._Equal("buildBuildingsoldier") && message._players[0].getIsBase())
		{
			if (message._players[0].getMoney()<BUIDSOLDIER_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			else if (message._players[0].getPower()<BUIDSOLDIER_POWER)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the power!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - BUIDSOLDIER_PRICE);
			message._players[0].setPower(message._players[0].getPower() - BUIDSOLDIER_POWER);
			log("buildingsoldier was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			
			auto buildingsoldier = Building::create("buildingsoldier.png");
			map->addChild(buildingsoldier, 20);
			buildingsoldier->initBuilding(putPosition, BUIDSOLDIER_TYPE);
			auto physicsBodyFD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyFD->setGravityEnable(false);
			physicsBodyFD->setDynamic(false);
			buildingsoldier->addComponent(physicsBodyFD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			buildingsoldier->setblood(buildingblood);
			buildingsoldier->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));
			_buildings.push_back(buildingsoldier);
			int i = 0;
			for (auto x : _buildings)
			{
				if (x == buildingsoldier)
				{
					_buildings[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^24" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")"+ std::to_string(message._players[0].index * 1250 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}

			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the buildingsoldier is，%f,%f", putPosition.x, putPosition.y);
		}
		else if (message.getOrder()._Equal("buildBuildingpower") && message._players[0].getIsBase())
		{
			if (message._players[0].getMoney()<BUIDPOWER_PRICE)
			{
				auto toast = Toast::create("Are you kidding?Please pay attention to the money!", 20, 1);
				this->addChild(toast);
				message.clean();
				log("order is clean");
				return true;
			}
			message._players[0].setMoney(message._players[0].getMoney() - BUIDPOWER_PRICE);
			message._players[0].setPower(message._players[0].getPower() + BUIDPOWER_POWER);
			log("buildingpower was build!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("tilePosition %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("TouchPosition %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("PutPoisition %f,%f", putPosition.x, putPosition.y);
			
			auto buildingpower = Building::create("buildingpower.png");//
			buildingpower->initBuilding(putPosition, BUIDPOWER_TYPE);//
			map->addChild(buildingpower, 20);//
			auto physicsBodyFD = PhysicsBody::createCircle(50,
				PhysicsMaterial(0.1f, 0.0f, 0.0f));
			physicsBodyFD->setGravityEnable(false);
			physicsBodyFD->setDynamic(false);
			buildingpower->addComponent(physicsBodyFD);
			std::string sbuildingblood = "blood" + std::to_string(message._players[0].index) + ".png";
			auto buildingblood = Sprite::create(sbuildingblood.c_str());
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			buildingpower->setblood(buildingblood);
			buildingpower->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			buildingbar->setPosition(Vec2(putPosition.x, putPosition.y + 50));
			buildingblood->setPosition(Vec2(putPosition.x - 50, putPosition.y + 50));    /***********************************************/
			_buildings.push_back(buildingpower);
			int i = 0;
			for (auto x : _buildings)
			{
				if (x == buildingpower)
				{
					_buildings[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^23" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")" + std::to_string(message._players[0].index * 1250 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}

			//log("我来看看瓦片地图的每个格子宽和高：%d,%f,%d,%f",tileSize.width,tileSize.width,tileSize.height,tileSize.height);
			log("where the buildingpower is，%f,%f", buildingblood->getPosition().x, buildingblood->getPosition().y);
		}
		else if (message.getOrder() == "move"&&message._players[0].getIsBase())
		{
			cocos2d::log("Move!");
			Vec2 touchPosition = touch->getLocation();
			Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
			Vec2 putPosition = this->positionForTileCoord(tilePosition, map);
			cocos2d::log("瓦片地图坐标在哪呢 %f,%f", tilePosition.x, tilePosition.y);
			cocos2d::log("触摸坐标在哪呢 %f,%f", touchPosition.x, touchPosition.y);
			cocos2d::log("放置坐标在哪呢 %f,%f", putPosition.x, putPosition.y);
			message.getTargetOne()->moveMoveable(putPosition);
			int tage = message.getTargetOne()->getTag();
			//加一个序列号置于*后面
			std::string mess_age = message._players[0].name + "*" + std::to_string(tage) + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}
		}

		message.clean();
		log("order is clean");
		return true;
	};

	initxy();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenermap, map);
	schedule(schedule_selector(MapScene::orderupdate), 0.01f);
	schedule(schedule_selector(MapScene::moneyupdate), 0.1f);
	scheduleUpdate();
	return true;
}

void MapScene::menuBack(Ref* pSender)
{
	Director::sharedDirector()->replaceScene(HelloWorld::createScene());
}

void MapScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	if (message.mapindex == 1)
	{
		auto diff = touches[0]->getDelta();
		cocos2d::log("diff.x diff.y %f,%f", diff.x, diff.y);

		auto node = getChildByTag(100);
		auto currentPos = node->getPosition();
		if ((currentPos + diff).x <= 0 && (currentPos + diff).y <= 0 && (currentPos + diff).x >= -5610 - 166
			+ Director::getInstance()->getVisibleSize().width && (currentPos + diff).y >= -2739 + Director::getInstance()->getVisibleSize().height)
		{
			node->setPosition(currentPos + diff);
			dx += diff.x;
			dy += diff.y;
		}
	}
	else if (message.mapindex == 2)
	{
		auto diff = touches[0]->getDelta();
		cocos2d::log("diff.x diff.y %f,%f", diff.x, diff.y);

		auto node = getChildByTag(100);
		auto currentPos = node->getPosition();
		if ((currentPos + diff).x <= 0 && (currentPos + diff).y <= 0 && (currentPos + diff).x >= -5841 - 166
			+ Director::getInstance()->getVisibleSize().width && (currentPos + diff).y >= -1452 + Director::getInstance()->getVisibleSize().height)
		{
			node->setPosition(currentPos + diff);
			dx += diff.x;
			dy += diff.y;
		}
	}
}


void MapScene::prebase()
{
	int i = 0;
	std::string allusername;
	for (auto x : message._players)
	{
		if (message._players[i].index == 1)
		{
			allusername = message._players[i].name;
			auto base0 = BuildingBase::create("base.png");
			base0->setTag(BUIDBASE_TYPE);
			base0->initBase(BUIDBASE_TYPE);
			map->addChild(base0, 20);
			_bases[base0] = allusername;
			auto buildingblood = Sprite::create("blood.png");
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			base0->setblood(buildingblood);
			base0->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			if (message.mapindex == 1)
			{
				base0->setPosition(1534, 1270);
				buildingbar->setPosition(1534, 1320);
				buildingblood->setPosition(1484, 1320);
				map->setPosition(Vec2(-1300, -1100));
			}
			else if (message.mapindex == 2)
			{
				base0->setPosition(148, 1039);
				buildingbar->setPosition(148, 1089);
				buildingblood->setPosition(98, 1089);
				map->setPosition(Vec2(0, -700));
			}
		}
		else if (message._players[i].index == 2)
		{
			allusername = message._players[i].name;
			auto base1 = BuildingBase::create("base.png");    //把地址定下来，后面相同
			base1->setTag(BUIDBASE_TYPE);
			base1->initBase(BUIDBASE_TYPE);
			map->addChild(base1, 20);
			_bases[base1] = allusername;
			auto buildingblood = Sprite::create("blood.png");
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			base1->setblood(buildingblood);
			base1->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			if (message.mapindex == 1)
			{
				base1->setPosition(3085, 2293);
				buildingbar->setPosition(3085, 2343);
				buildingblood->setPosition(3035, 2343);
				map->setPosition(Vec2(-2900, -2100));
			}
			else if (message.mapindex == 2)
			{
				base1->setPosition(2392, 148);
				buildingbar->setPosition(2392, 198);
				buildingblood->setPosition(2342, 198);
				map->setPosition(Vec2(-2200, 0));
			}
		}
		else if (message._players[i].index == 3)
		{
			allusername = message._players[i].name;
			auto base2 = BuildingBase::create("base.png");
			base2->setTag(BUIDBASE_TYPE);
			base2->initBase(BUIDBASE_TYPE);
			map->addChild(base2, 20);
			_bases[base2] = allusername;
			auto buildingblood = Sprite::create("blood.png");
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			base2->setblood(buildingblood);
			base2->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			if (message.mapindex == 1)
			{
				base2->setPosition(4438, 1369);
				buildingbar->setPosition(4438, 1419);
				buildingblood->setPosition(4388, 1419);
				map->setPosition(Vec2(-4200, -1150));
			}
			else if (message.mapindex == 2)
			{
				base2->setPosition(5659, 511);
				buildingbar->setPosition(5659, 561);
				buildingblood->setPosition(5609, 561);
				map->setPosition(Vec2(-5450, -300));
			}
		}
		else if (message._players[i].index == 4)
		{
			allusername = message._players[i].name;
			auto base3 = BuildingBase::create("base.png");
			base3->setTag(BUIDBASE_TYPE);
			base3->initBase(BUIDBASE_TYPE);
			map->addChild(base3, 20);
			_bases[base3] = allusername;
			auto buildingblood = Sprite::create("blood.png");
			buildingblood->setAnchorPoint(Vec2(0, 0.5));
			auto buildingbar = Sprite::create("bar.png");
			base3->setblood(buildingblood);
			base3->setbar(buildingbar);
			map->addChild(buildingbar, 21);
			map->addChild(buildingblood, 22);
			if (message.mapindex == 1)
			{
				base3->setPosition(2887, 247);
				buildingbar->setPosition(2887, 297);
				buildingblood->setPosition(2837, 297);
				map->setPosition(Vec2(-2700, -47));
			}
			else if (message.mapindex == 2)
			{
				base3->setPosition(2425, 1105);
				buildingbar->setPosition(2425, 1155);
				buildingblood->setPosition(2375, 1155);
				map->setPosition(Vec2(-2200, -900));
			}
		}
		i++;
	}
}
void MapScene::update(float dt)
{
	int i = 0;
	int carfcount = 0, soldiefrcount = 0;
	for (auto& x : _buildings)
	{

		if (x->getType() == 0)
		{
			map->removeChild(_buildings[i]->getblood());
			map->removeChild(_buildings[i]->getbar());
			map->removeChild(_buildings[i]);
		}
		if (x->getType() == BUIDSOLDIER_TYPE)
			soldiefrcount++;
			/*message._players[0].setIsSoldierFactory(true);*/
		if (x->getType() == BUIDCAR_TYPE)
			carfcount++;
			/*message._players[0].setIsCarFactory(true);*/
		i++;
	}
	if (carfcount == 0)
	{
		message._players[0].setIsCarFactory(false);
	}
	else
	{
		message._players[0].setIsCarFactory(true);
	}
	if (soldiefrcount == 0)
	{
		message._players[0].setIsSoldierFactory(false);
	}
	else
	{
		message._players[0].setIsSoldierFactory(true);
	}
	for (auto x : _bases)
	{
		if (x.second == message._players[0].name)
		{
			if (x.first->getType() == 0)
			{
				message._players[0].setIsBase(false);
			}
			break;
		}
	}
	i = 0;
	for (auto x : _buildingsE)
	{
		if (x->getType() == 0)
		{
			map->removeChild(_buildingsE[i]->getblood());
			map->removeChild(_buildingsE[i]->getbar());
			map->removeChild(_buildingsE[i]);
		}
		i++;
	}
	i = 0;
	for (auto x : _moveables)
	{
		if (x->getType() == 0)
		{
			map->removeChild(_moveables[i]->getblood());
			map->removeChild(_moveables[i]->getbar());
			map->removeChild(_moveables[i]);
		}
		i++;
	}
	i = 0;
	for (auto x : _moveablesE)
	{
		if (x->getType() == 0)
		{
			map->removeChild(_moveablesE[i]->getblood());
			map->removeChild(_moveablesE[i]->getbar());
			map->removeChild(_moveablesE[i]);
		}
		i++;
	}
	for (auto& x : _bases)
	{
		if (x.first->getType() == 0)
		{
			map->removeChild(x.first->getblood());
			map->removeChild(x.first->getbar());
			map->removeChild(x.first);
		}
	}
}

void MapScene::orderupdate(float dt)
{
	for (auto& x : message._orderlist)
	{
		if (x.mode == 1 && x._username != message._players[0].name)
		{
			if (x.attack < 14 && x.attack >= 11 )
			{
				auto moves = Moveable::create("soldierleft.png");
				map->addChild(moves, 20);
				auto physicsBodyD = PhysicsBody::createCircle(50,
					PhysicsMaterial(0.1f, 0.0f, 0.0f));
				physicsBodyD->setGravityEnable(false);
				moves->addComponent(physicsBodyD);
				moves->addMoveable(x.putposition, x.attack);
				moves->setTag(x.tage);
				int bloodcount = 0;
				for (auto y : message._players)
				{
					if (y.name == x._username)
					{
						bloodcount = y.index;
					}
				}
				std::string sbuildingblood = "blood" + std::to_string(bloodcount) + ".png";
				auto buildingblood = Sprite::create(sbuildingblood.c_str());
				buildingblood->setAnchorPoint(Vec2(0, 0.5));
				auto buildingbar = Sprite::create("bar.png");
				moves->setblood(buildingblood);
				moves->setbar(buildingbar);
				map->addChild(buildingbar, 21);
				map->addChild(buildingblood, 22);
				buildingbar->setPosition(Vec2(x.putposition.x, x.putposition.y + 50));
				buildingblood->setPosition(Vec2(x.putposition.x - 50, x.putposition.y + 50));
				_moveablesE.push_back(moves);
			}
			else if (x.attack > 21 && x.attack < 26 )
			{
				auto buildings = Building::create("base.png");
				auto physicsBodyD = PhysicsBody::createCircle(50,
					PhysicsMaterial(0.1f, 0.0f, 0.0f));
				physicsBodyD->setGravityEnable(false);
				physicsBodyD->setDynamic(false);
				buildings->addComponent(physicsBodyD);
				map->addChild(buildings, 20);
				buildings->initBuilding(x.putposition, x.attack);
				buildings->setTag(x.tage);
				int bloodcount = 0;
				for (auto y : message._players)
				{
					if (y.name == x._username)
					{
						bloodcount = y.index;
					}
				}
				std::string sbuildingblood = "blood" + std::to_string(bloodcount) + ".png";
				auto buildingblood = Sprite::create(sbuildingblood.c_str());
				buildingblood->setAnchorPoint(Vec2(0, 0.5));
				auto buildingbar = Sprite::create("bar.png");
				buildings->setblood(buildingblood);
				buildings->setbar(buildingbar);
				map->addChild(buildingbar, 21);
				map->addChild(buildingblood, 22);
				buildingbar->setPosition(Vec2(x.putposition.x, x.putposition.y + 50));
				buildingblood->setPosition(Vec2(x.putposition.x - 50, x.putposition.y + 50));
				_buildingsE.push_back(buildings);
			}
		}
		else if (x.mode == 2 && x._username != message._players[0].name)
		{
			Moveable * targetone = NULL;
			Moveable * targettwo = NULL;
			for (auto& y : _moveables)
			{
				if (targetone&&targettwo)
					break;
				if (y->getTag() == x.attack)
				{
					targetone = y;
				}
				if (y->getTag() == x.isattack)
				{
					targettwo = y;
				}
			}
			for (auto& y : _moveablesE)
			{
				if (targetone&&targettwo)
					break;
				if (y->getTag() == x.attack)
				{
					targetone = y;
				}
				if (y->getTag() == x.isattack)
				{
					targettwo = y;
				}
			}
			targettwo->isattacked(targetone);
		}
		else if (x.mode == 3 && x._username != message._players[0].name)
		{
			for (auto& y : _moveablesE)
			{
				if (y->getTag() == x.attack)
				{
					y->moveMoveable(x.putposition);
					break;
				}
			}
		}
		if(message._orderlist.size()!=0)
			message._orderlist.pop_front();
		break;
	}
}

void MapScene::moneyupdate(float dt)
{
	int moneycount = 0;
	int powercount = 0;
	for (auto x : _buildings)
	{
		if (x->getType() == BUIDMINE_TYPE)
		{
			moneycount++;
		}
		else if (x->getType() == BUIDPOWER_TYPE)
		{
			powercount++;
		}
	}
	message._players[0].setMoney(message._players[0].getMoney() + 10 * moneycount);
	moneyboard->setScore(message._players[0].getMoney());
	powerboard->setScore(message._players[0].getPower());
}

void MapScene::initxy()
{
	switch (message._players[0].index)
	{
	case 1:
		if (message.mapindex == 1)
		{
			dx = 1300;
			dy = 1100;
		}
		else
		{
			dx = 0;
			dy = -700;
		}
		break;
	case 2:
		if (message.mapindex == 1)
		{
			dx = 2900;
			dy = 2100;
		}
		else
		{
			dx = 2200;
			dy = 0;
		}
		break;
	case 3:
		if (message.mapindex == 1)
		{
			dx = 4200;
			dy = 1150;
		}
		else
		{
			dx = 5450;
			dy = 300;
		}
		break;
	case 4:
		if (message.mapindex == 1)
		{
			dx = 2700;
			dy = 47;
		}
		else
		{
			dx = 2200;
			dy = 900;
		}
		break;
	}
}