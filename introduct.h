#pragma once

#include<list>
#include "cocos2d.h"

class introduct
{
public:
	int mode = 0;
	std::string _username ;
	int attack=0 ;    //���������ͣ��ƶ���Ŀ�꣬�����Ĺ�����
	cocos2d::Vec2 putposition ;
	int isattack=0 ;
	int tage=0 ;//�����ı�ǩ
	bool operator ==(const introduct& a)const;
};
