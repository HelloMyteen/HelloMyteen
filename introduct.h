#pragma once

#include<list>
#include "cocos2d.h"

class introduct
{
public:
	int mode = 0;
	std::string _username ;
	int attack=0 ;    //创建的类型，移动的目标，攻击的攻击者
	cocos2d::Vec2 putposition ;
	int isattack=0 ;
	int tage=0 ;//创建的标签
	bool operator ==(const introduct& a)const;
};
