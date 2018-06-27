//
//  Player.h
//  experiment
//
//  Created by 叶琪 on 2018/6/23.
//

#pragma once

#include <string>

class Player
{
public:
    
    std::string getPlayerName();
    bool getHost();
    bool getDead();
    int getMoney();
    int getPower();
    bool getIsCarFactory();
    bool getIsSoldierFactory();
	bool getready();
	bool getIsBase();

	void setready();
    void setPlayerName(const std::string str);
    void setHost(bool b);
    void setDead(bool b);
    void setMoney(int m);
	void setPower(int m);
    void setIsCarFactory(bool b);
    void setIsSoldierFactory(bool b);
	void setIsBase(bool k);

	std::string name;
	bool readyflag = false;
	int index = 0;      //玩家序列号，可为1，2，3，4
	int flag = 0;    //属性flag , 1：自服   2：自客    3：服    4：客
	bool labelflag = false;     //是否已经贴标签
private:
    bool isHost;
	bool ready = false;     //是否准备
    bool isDead;
	int money = 2000;
	int power = 0;
    bool isCarFactory=false;
    bool isSoldierFactory=false;
	bool isBase = true;
};

