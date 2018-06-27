#pragma once


#include <iostream>
#include"game_unit.h"
#include "BuildingData.h"
#include "Moveable.h"


class Moveable;

class BuildingBase:public GameUnit
{
public:
	BuildingBase() = default;


	//基地的创建
	static BuildingBase* create(const std::string & filename);

	static BuildingBase* createWithSpriteFrameName(const std::string & filename);

	//初始化本地基地
	void   initBase(int type);

	void EraseBase();

	void boomlisten();

	void isattacked_(Moveable* target);

	cocos2d::EventListenerTouchOneByOne* baselistener;


};