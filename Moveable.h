#pragma once

#include <cocos2d.h>
#include "game_unit.h"
#include "moveable_data.h"
#include "Toast.h"

class Moveable:public GameUnit
{
public:

	int count = 0;
	Moveable() = default;
	static Moveable* create(const std::string& filename);
	static Moveable* createWithSpriteFrameName(const std::string & filename);
 
    void update(float dt);
    void updateGum(float dt);

	void eraseMoveable();
	void moveMoveable(cocos2d::Vec2 destination);

	bool canattack(Moveable* target);
	

	void isattacked(Moveable* target);
	

	float getMoveSpeed();
	void setMoveSpeed(float speed);
	
	bool getAttackable();
	void setAttackable(const bool b);

	bool getDirect();
	std::string getDirection();
	void changeDirect(const bool dir);

	std::string getTypeName();
	void setTypeName(const std::string str);

	void addMoveable(const cocos2d::Vec2 pos, int type);

	//动作监听的回调函数
	void movelisten();

	/*以下是龙宇写的血条变化的函数*/
	void updateBloodBar(int Health, int MaxHealth, cocos2d::Sprite* _blood);

private:
	bool attackable;//擦枪时间
	float movespeed;
	bool isSelected;
	cocos2d::EventListenerTouchOneByOne* listener;
	std::string type_name;

	//为假向左，字符串为left，移动方向x小于0
	bool direction;
	std::string direct;
};


