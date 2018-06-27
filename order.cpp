#include "order.h"

void Message::clean()
{
	target1 = nullptr;
	target2 = nullptr;
	player1.clear();
	player2.clear();
	order.clear();
}

std::string Message::getOrder()
{
	return order;
}

std::string Message::getPlayerOne()
{
	return player1;
}

std::string Message::getPlayerTwo()
{
	return player2;
}

Moveable * Message::getTargetOne()
{
	return target1;
}

Moveable * Message::getTargetTwo()
{
	return target2;
}

void Message::setOrder(const std::string str)
{
	order = str;
}

void Message::setPlayerOne(const std::string str)
{
	player1 = str;
}

void Message::setPlayerTwo(const std::string str)
{
	player2 = str;
}

void Message::setTargetOne( Moveable * unit)
{
	target1 = unit;
}

void Message::setTargetTwo(Moveable * unit)
{
	target2 = unit;
}

//ÍøÂç¿âĞèÇó
void Message::setOpName(std::string name)
{
	operatename = name;
}
void Message::setOpPos(Vec2 pos)
{
	operateposition = pos;
}
std::string Message::getOperteName()
{
	return operatename;
}
Vec2 Message::getOpertePos()
{
	return operateposition;
}