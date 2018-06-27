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
	log("%s", data);
	executeP(data);
	message._server->sendMessage(data, count);
}
void onclientrecvP(const char* data, int count)
{
	log("%s", data);
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

	map = TMXTiledMap::create("untitled.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(Vec2(0, 0));

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
			i++;
		}
		message._server->sendMessage(nameindex.c_str(), nameindex.length());
		cocos2d::log("%s", nameindex.c_str());
	}

	prebase();

	cocos2d::Size mapSize = map->getMapSize();

	auto* Menu = Sprite::create("Menu.png");
	Menu->setAnchorPoint(Vec2(1,1));
	Menu->setPosition(size.width, size.height);
	addChild(Menu);
	/*********************                  SELL                   **************************/
	menuSell = Sprite::create("Sell.png");
	menuSell->setPosition(size.width - 60,size.height / 2 + 140);
	this->addChild(menuSell, 4);

	auto listenerSell = EventListenerTouchOneByOne::create();
	listenerSell->setSwallowTouches(true);
	listenerSell->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			log("order is clean!");
			message.clean();
			message.setOrder("sell");
			log("SELL");
			auto toast = Toast::create("WARNING! You will sell unit!!");
			this->addChild(toast);
			return true;
		}
		else
		{
			return false;
		}
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSell, menuSell);
	/*********************                  SELL                   **************************/





	/********************                   MINE              *********************************/
	menuMine = Sprite::create("buildingmine.png");
	menuMine->setPosition(size.width - 115, size.height / 2 + 70);
	menuMine->setScale(0.5f);
	menuMine->setTag(Mine_TYPE);
	this->addChild(menuMine, 4);

	//菜单栏上矿厂的监听器
	auto listenermine  = EventListenerTouchOneByOne::create();
	listenermine->setSwallowTouches(true);
	listenermine->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			if (isMine)
			{
				log("order is clean!");
				message.clean();
				message.setOrder("buildmine");
				log("mine in menu is touched! You will build a mine if you touch map");
				return true;
			}
			else
			{
				auto toast = Toast::create("Cold Down", 20, 1);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenermine, menuMine);
	/***************************************************************************************/




	/********************                   BuildingCar              *********************************/
	menuCarFac = Sprite::create("buildingcar.png");
	menuCarFac->setPosition(size.width - 115, size.height / 2 + 20);
	menuCarFac->setScale(0.5f);
	menuCarFac->setTag(Car_TYPE);
	this->addChild(menuCarFac, 4);

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
			if (isCarFac)
			{
				log("order is clean!");
				message.clean();
				message.setOrder("buildBuildingcar");
				log("buildingcar in menu is touched! You will build a mine if you touch map");
				return true;
			}
			else
			{
				auto toast = Toast::create("Cold Down", 20, 1);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingcar, menuCarFac);
	/***************************************************************************************/



	/********************                   BuildingSoldier              *********************************/
	menuSoldierFac = Sprite::create("buildingsoldier.png");
	menuSoldierFac->setPosition(size.width - 115, size.height / 2 -30);
	menuSoldierFac->setScale(0.5f);
	menuSoldierFac->setTag(Soldier_TYPE);
	this->addChild(menuSoldierFac, 4);

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
			if (isSoldierFac)
			{
				log("order is clean!");
				message.clean();
				message.setOrder("buildBuildingsoldier");
				log("buildingsoldier in menu is touched! You will build a mine if you touch map");
				return true;
			}
			else
			{
				auto toast = Toast::create("Cold Down", 20, 1);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingsoldier, menuSoldierFac);
	/***************************************************************************************/

	/********************                   BuildingPower              *********************************/
	menuPower = Sprite::create("buildingpower.png");
	menuPower->setPosition(size.width - 115, size.height / 2-80);
	menuPower->setScale(0.5f);
	menuPower->setTag(Power_TYPE);
	this->addChild(menuPower, 4);

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
			if (isPower)
			{
				log("order is clean!");
				auto toast = Toast::create(
					"soldier in menu is touched! You will build a soldier if you touch map", 20, 2);
				this->addChild(toast);
				message.clean();
				message.setOrder("buildBuildingpower");
				return true;
			}
			else
			{
				auto toast = Toast::create("Cold Down", 20, 1);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerbuildingpower, menuPower);
	/***************************************************************************************/

	/***********************               SOLDIER          ********************************/
	menuSoldier = Sprite::create("soldierleft.png");
	menuSoldier->setPosition(size.width - 115, size.height / 2 -130);
	menuSoldier->setScale(0.4f);
	menuSoldier->setTag(SOLDIER_TYPE);
	this->addChild(menuSoldier, 4);
	isSoldier = true;
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
			if (message._players[0].getIsSoldierFactory()&&isSoldier)
				/* 这里判断是否存在兵营并且是否在空档期 */
			{
				log("order is clean!");
				auto toast = Toast::create(
					"soldier in menu is touched! You will build a soldier if you touch map", 20, 3);
				this->addChild(toast);
				message.clean();
				message.setOrder("buildsoldier");
				return true;
			}
			else
				/* 不存在应该给个弹窗提示无兵营不允许创建坦克 */
			{
				auto toast = Toast::create(
					"You don't build it.", 20, 1);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenersoldier, menuSoldier);
	/********************                  SOLDIER                 *****************************/





	/********************                  TANK                       **************************/
	menuTank = Sprite::create("tankleft.png");
	menuTank->setPosition(size.width - 115, size.height / 2 - 180);
	menuTank->setScale(0.4f);
	menuTank->setTag(TANK_TYPE);
	this->addChild(menuTank, 4);
	isTank = true;
	//菜单栏上大兵的监听器
	auto listenertank = EventListenerTouchOneByOne::create();
	listenertank->setSwallowTouches(true);
	listenertank->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			if (message._players[0].getIsCarFactory() && isTank)
				/* 这里判断是否存在兵营并且是否在空档期 */
			{
				log("order is clean!");
				auto toast = Toast::create(
					"tank in menu is touched! You will build a tank if you touch map", 20, 3);
				this->addChild(toast);
				message.clean();
				message.setOrder("buildtank");
				return true;
			}
			else
				/* 不存在应该给个弹窗提示无兵营不允许创建坦克 */
			{
				auto toast = Toast::create(
					"You don't build it.", 20, 3);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenertank, menuTank);

	/********************                  TANK                       **************************/


	/*********************                 DOG                         ***************************/
	menuDog = Sprite::create("dogleft.png");
	menuDog->setPosition(size.width - 115, size.height / 2 - 230);
	menuDog->setScale(0.4f);
	menuDog->setTag(DOG_TYPE);
	this->addChild(menuDog, 4);
	isDog = true;
	//菜单栏上大兵的监听器
	auto listenerdog = EventListenerTouchOneByOne::create();
	listenerdog->setSwallowTouches(true);
	listenerdog->onTouchBegan = [this](Touch *t, Event *e)
	{

		auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标

		Point locationInNode = target->convertToNodeSpace(t->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			if (message._players[0].getIsSoldierFactory() && isDog)
				/* 这里判断是否存在兵营并且是否在空档期 */
			{
				log("order is clean!");
				auto toast = Toast::create(
					"dog in menu is touched! You will build a dog if you touch map", 20, 3);
				this->addChild(toast);
				message.clean();
				message.setOrder("builddog");
				return true;
			}
			else
				/* 不存在应该给个弹窗提示无兵营不允许创建坦克 */
			{
				auto toast = Toast::create(
					"You don't build it.", 20, 3);
				this->addChild(toast);
			}
		}
		else
		{
			return false;
		}


	};

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerdog, menuDog);
	/*********************                 DOG                         ***************************/





	/*******************************************************************************************************************************************/

	/******************               MAP LISTENER                   ***************************/
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

		Vec2 touchPosition = touch->getLocation();
		Vec2 tilePosition = this->tileCoordForPosition(touchPosition, map);
		Vec2 putPosition = this->positionForTileCoord(tilePosition, map);



		if (message.getOrder().find("build") != message.getOrder().size())
		{
			cocos2d::Vec2 basePos;
			for (auto x : _bases)
			{
				if (x.second == message._players[0].name)
				{
					basePos = x.first->getPosition();
					break;
				}
			}
			float distance = putPosition.distance(basePos);
			if (distance > Base_EFFECT)
			{
				message.clean();
				auto toast = Toast::create("Too far away! Retry", 25, 1);
				this->addChild(toast);
				return true;
			}
		}



		/***************************        BUILD   DOG     ORDER                      ********************************/
		if (message.getOrder() == "builddog" && message._players[0].getIsSoldierFactory())
		{
			auto dog = Moveable::create("dogleft.png");
			map->addChild(dog, 20);
			dog->addMoveable(putPosition, DOG_TYPE);
			_moveables.push_back(dog);
			isDog = false;
			auto frame = cocos2d::SpriteFrame::create("dogblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuDog->setScale(0.3f);
			menuDog->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeDog), DOG_BUILD_TIME);

			int i = 0;
			for (auto x : _moveables)
			{
				if (x == dog)
				{
					_moveables[i]->setTag(message._players[0].index * 1000 + i);
					break;
				}
				i++;
			}
			std::string mess_age = message._players[0].name + "^13" + "(" + std::to_string(putPosition.x) + ","
				+ std::to_string(putPosition.y) + ")" + std::to_string(message._players[0].index * 1000 + i) + "%";
			if (message._players[0].flag == 1)
			{
				message._server->sendMessage(mess_age.c_str(), mess_age.length());
			}
			else
			{
				message._client->sendMessage(mess_age.c_str(), mess_age.length());
			}
		}
		/***************************        BUILD   DOG     ORDER                      ********************************/






		/***************************        BUILD   CAR     ORDER                      ********************************/
		else if (message.getOrder() == "buildtank"&&message._players[0].getIsCarFactory())
		{
			log("car was build!");
			auto tank = Moveable::create("tankleft.png");
			map->addChild(tank, 20);
			tank->addMoveable(putPosition, TANK_TYPE);
			_moveables.push_back(tank);
			isTank = false;
			auto frame = cocos2d::SpriteFrame::create("tankblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuTank->setScale(0.3f);
			menuTank->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeTank), TANK_BUILD_TIME);

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
		/***************************        BUILD   CAR     ORDER                      ********************************/






		/***************************        BUILD   SOLDIER     ORDER                      ********************************/
		else if (message.getOrder() == "buildsoldier"&&message._players[0].getIsSoldierFactory())
		{
			log("soldier was build!");
			auto soldier = Moveable::create("soldierleft.png");
			map->addChild(soldier, 20);
			soldier->addMoveable(putPosition, SOLDIER_TYPE);
			_moveables.push_back(soldier);

			isSoldier = false;
			auto frame = cocos2d::SpriteFrame::create("soldierblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuSoldier->setScale(0.3f);
			menuSoldier->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeSoldier), SOLDIER_BUILD_TIME);

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
			/*message.moveables[i]->addMoveable(putPosition, SOLDIER_TYPE);
			message.moveables[i]->setTag(message._players[0].index * 1000 + i);*/
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
		/***************************        BUILD   SOLDIER     ORDER                      ********************************/




		/***************************        BUILDMINW  ORDER                      ****************************************/
		else if (message.getOrder() == "buildmine"&&message._players[0].getIsBase())
		{
			log("mine was build!");
			auto mine = Building::create("buildingmine.png");
			map->addChild(mine, 20);
			mine->initBuilding(putPosition, Mine_TYPE);
			_buildings.push_back(mine);

			isMine = false;
			auto frame = cocos2d::SpriteFrame::create("buildingmineblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuMine->setScale(0.5f);
			menuMine->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeMine), Mine_BUILD_TIME);

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
			log("where the mine is，%f,%f", putPosition.x, putPosition.y);
		}
		/***************************        BUILDMINW  ORDER                      ****************************************/





		/***************************        BUILDCARFAC  ORDER                      ****************************************/
		else if (message.getOrder()._Equal("buildBuildingcar") && message._players[0].getIsBase())
		{
			log("buildingcar was build!");
			auto buildingcar = Building::create("buildingcar.png");
			map->addChild(buildingcar, 20);
			buildingcar->initBuilding(putPosition, Car_TYPE);
			_buildings.push_back(buildingcar);

			isCarFac = false;
			auto frame = cocos2d::SpriteFrame::create("buildingcarblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuCarFac->setScale(0.5f);
			menuCarFac->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeCarFac), Car_BUILD_TIME);


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
			/*message.buildings[i]->initBuilding(putPosition, Car_TYPE);
			message.buildings[i]->setTag(message._players[0].index * 1250 + i);*/
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

			log("where the buildingcar is，%f,%f", putPosition.x, putPosition.y);
		}
		/***************************        BUILDCARFAC  ORDER                      ****************************************/


		/***************************        BUILDSOLDIERFAC  ORDER                      ****************************************/
		else if (message.getOrder()._Equal("buildBuildingsoldier") && message._players[0].getIsBase())
		{
			log("buildingsoldier was build!");	
			auto buildingsoldier = Building::create("buildingsoldier.png");
			map->addChild(buildingsoldier, 20);
			buildingsoldier->initBuilding(putPosition, Soldier_TYPE);
			_buildings.push_back(buildingsoldier);

			isSoldierFac = false;
			auto frame = cocos2d::SpriteFrame::create("buildingsoldierblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuSoldierFac->setScale(0.5f);
			menuSoldierFac->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changeSoldierFac), Soldier_BUILD_TIME);

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
			log("where the buildingsoldier is，%f,%f", putPosition.x, putPosition.y);
		}
		/***************************        BUILDSOLDIERFAC  ORDER                      ****************************************/



		/***************************        BUILDPOWER  ORDER                      ****************************************/
		else if (message.getOrder()._Equal("buildBuildingpower") && message._players[0].getIsBase())
		{
			log("buildingpower was build!");
			auto buildingpower = Building::create("buildingpower.png");
			map->addChild(buildingpower, 20);
			buildingpower->initBuilding(putPosition, Power_TYPE);
			_buildings.push_back(buildingpower);

			isPower = false;
			auto frame = cocos2d::SpriteFrame::create("buildingpowerblack.png", cocos2d::Rect(0, 0, 99, 99));
			menuPower->setScale(0.5f);
			menuPower->setDisplayFrame(frame);
			this->scheduleOnce(schedule_selector(MapScene::changePower), Power_BUILD_TIME);

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
			log("where the buildingpower is，%f,%f", putPosition.x, putPosition.y);
		}

		/***************************        BUILDPOWER  ORDER                      ****************************************/



		else if (message.getOrder() == "move"&&message._players[0].getIsBase())
		{
			cocos2d::log("Move!");
			message.getTargetOne()->moveMoveable(putPosition);
			int tage=message.getTargetOne()->getTag();
			std::string mess_age = message._players[0].name + "*"+ std::to_string(tage)+ "(" + std::to_string(putPosition.x) + ","
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

	eventDispatcher->addEventListenerWithSceneGraphPriority(listenermap, map);
	schedule(schedule_selector(MapScene::orderupdate), 0.01f);
	scheduleUpdate();
    return true;
}

void MapScene::menuBack(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(HelloWorld::createScene());
}

void MapScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    auto diff = touches[0]->getDelta();
	dx += diff.x;
	dy += diff.y;
    auto node = getChildByTag(100);
    auto currentPos = node->getPosition();
    node->setPosition(currentPos + diff);


}

void MapScene::prebase()
{
	int i = 0;
	std::string allusername;
	for (auto x : message._players)
	{
		if (i == 0)
		{
			allusername = message._players[i].name;
			auto base0 = BuildingBase::create("base.png");
			base0->setPosition(1534, 1270);
			base0->setTag(Base_TYPE);
			base0->initBase(Base_TYPE);
			map->addChild(base0, 20);
			_bases[base0] = allusername;
		}
		else if (i == 1)
		{
			allusername = message._players[i].name;
			auto base1 = BuildingBase::create("base.png");    //把地址定下来，后面相同
			base1->setPosition(3085, 2293);
			base1->setTag(Base_TYPE);
			base1->initBase(Base_TYPE);
			map->addChild(base1, 20);
			_bases[base1] = allusername;
		}
		else if (i == 2)
		{
			allusername = message._players[i].name;
			auto base2 = BuildingBase::create("base.png");
			base2->setPosition(4438, 1369);
			base2->setTag(Base_TYPE);
			base2->initBase(Base_TYPE);
			map->addChild(base2, 20);
			_bases[base2] = allusername;
		}
		else if (i == 3)
		{
			allusername = message._players[i].name;
			auto base3 = BuildingBase::create("base.png");
			base3->setPosition(2887, 247);
			base3->setTag(Base_TYPE);
			base3->initBase(Base_TYPE);
			map->addChild(base3, 20);
			_bases[base3] = allusername;
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
			map->removeChild(_buildings[i]);
		}
		if (x->getType() == Soldier_TYPE)
			soldiefrcount++;
		if (x->getType() == Car_TYPE)
			carfcount++;
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
			map->removeChild(_buildings[i]);
		}
		i++;
	}
	i = 0;
	for (auto x : _moveables)
	{
		if (x->getType() == 0)
		{
			map->removeChild(_moveables[i]);
		}
		i++;
	}
	i = 0;
	for (auto x : _moveablesE)
	{
		if (x->getType() == 0)
		{
			map->removeChild(_moveablesE[i]);
		}
		i++;
	}
}

void MapScene::setPhysicD(Sprite * sp)
{
	physicsBodyD->setGravityEnable(false);
	sp->addComponent(physicsBodyD);
}
void MapScene::setPhysicFD(Sprite * sp)
{
	physicsBodyFD->setGravityEnable(false);
	physicsBodyFD->setDynamic(false);
	sp->addComponent(physicsBodyFD);  //8888888888888888888888888888888暂时未添加刚体
}

void MapScene::orderupdate(float dt)
{
	for (auto& x : message._orderlist)
	{
		if (x.mode == 1 && x._username != message._players[0].name)
		{
			if (x.attack < 14 && x.attack >= 11)
			{
				auto moves = Moveable::create("soldierleft.png");
				map->addChild(moves, 20);
				moves->addMoveable(x.putposition, x.attack);
				moves->setTag(x.tage);
				_moveablesE.push_back(moves);

				/*message.moveablesE[i]->addMoveable(x.putposition, x.attack);
				message.moveablesE[i]->setTag(x.tage);*/
			}
			else if (x.attack > 21 && x.attack < 26)
			{
				auto buildings = Building::create("base.png");
				map->addChild(buildings, 20);
				buildings->initBuilding(x.putposition, x.attack);
				buildings->setTag(x.tage);
				_buildingsE.push_back(buildings);

				/*message.buildingsE[i]->initBuilding(x.putposition, x.attack);
				message.buildingsE[i]->setTag(x.tage);*/
			}
		}
		else if (x.mode == 2 && x._username != message._players[0].name)
		{
			/*auto targetone = (Moveable*)this->getChildByTag(x.attack);
			auto targettwo = (Moveable*)this->getChildByTag(x.isattack);*/

			Moveable* targetone = nullptr, *targettwo = nullptr;
			for (auto& target : _moveables)
			{
				if (targettwo&&targetone)
					break;
				if (target->getTag() == x.attack)
				{
					targetone = target;
				}
				if (target->getTag() == x.isattack)
				{
					targettwo = target;
				}
			}
			for (auto& target : _moveablesE)
			{
				if (targettwo&&targetone)
					break;
				if (target->getTag() == x.attack)
				{
					targetone = target;
				}
				if (target->getTag() == x.isattack)
				{
					targettwo = target;
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
		if (message._orderlist.size() != 0)
			message._orderlist.pop_front();
		break;
	}
}

void MapScene::changeTank(float dt)
{
	this->isTank = true;
	cocos2d::log("可以建坦克了");
	auto frame = cocos2d::SpriteFrame::create("tankleft.png", cocos2d::Rect(0, 0, 99, 99));
	menuTank->setDisplayFrame(frame);
	menuTank->setScale(0.3f);

}

void MapScene::changeSoldier(float dt)
{
	this->isSoldier = true;
	cocos2d::log("可以建兵了");
	auto frame = cocos2d::SpriteFrame::create("soldierleft.png", cocos2d::Rect(0, 0, 99, 99));
	menuSoldier->setDisplayFrame(frame);
	menuSoldier->setScale(0.3f);
}

void MapScene::changeDog(float dt)
{
	this->isDog = true;
	cocos2d::log("可以建狗了");
	auto frame = cocos2d::SpriteFrame::create("dogleft.png", cocos2d::Rect(0, 0, 99, 99));
	menuDog->setDisplayFrame(frame);
	menuDog->setScale(0.3f);
}

void MapScene::changeMine(float dt)
{
	this->isMine = true;
	cocos2d::log("可以建矿厂了");
	auto frame = cocos2d::SpriteFrame::create("buildingmine.png", cocos2d::Rect(0, 0, 99, 99));
	menuMine->setDisplayFrame(frame);
	menuMine->setScale(0.5f);
}

void MapScene::changePower(float dt)
{
	this->isPower = true;
	cocos2d::log("可以建电厂了");
	auto frame = cocos2d::SpriteFrame::create("buildingpower.png", cocos2d::Rect(0, 0, 99, 99));
	menuPower->setDisplayFrame(frame);
	menuPower->setScale(0.5f);
}

void MapScene::changeCarFac(float dt)
{
	this->isCarFac = true;
	cocos2d::log("可以建车厂了");
	auto frame = cocos2d::SpriteFrame::create("buildingcar.png", cocos2d::Rect(0, 0, 99, 99));
	menuCarFac->setDisplayFrame(frame);
	menuCarFac->setScale(0.5f);
}

void MapScene::changeSoldierFac(float dt)
{
	this->isSoldierFac = true;
	cocos2d::log("可以建兵厂了");
	auto frame = cocos2d::SpriteFrame::create("buildingsoldier.png", cocos2d::Rect(0, 0, 99, 99));
	menuSoldierFac->setDisplayFrame(frame);
	menuSoldierFac->setScale(0.5f);
}
