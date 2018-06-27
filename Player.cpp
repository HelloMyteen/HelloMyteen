//
//  Player.cpp
//  experiment-mobile
//
//  Created by 叶琪 on 2018/6/23.
//
#include "Player.h"

std::string Player::getPlayerName()
{
    return name;
}
bool Player::getready()
{
	return ready;
}
void Player::setready()
{
	ready = true;
}

bool Player::getHost()
{
    return isHost;
}

bool Player::getDead()
{
    return isDead;
}

int Player::getMoney()
{
    return money;
}

int Player::getPower()
{
    return power;
}

bool Player::getIsCarFactory()
{
    return isCarFactory;
}

bool Player::getIsSoldierFactory()
{
    return isSoldierFactory;
}


void Player::setPlayerName(const std::string str)
{
    name=str;
}
void Player::setHost(bool b)
{
    isHost=b;
}
void Player::setDead(bool b)
{
    isDead=b;
}
void Player::setMoney(int m)
{
    money=m;
}
void Player::setIsCarFactory(bool t)
{
    isCarFactory=t;
}

void Player::setIsSoldierFactory(bool f)
{
    isSoldierFactory=f;
}

void Player::setIsBase(bool k)
{
	isBase = k;
}

bool Player::getIsBase()
{
	return isBase;
}
