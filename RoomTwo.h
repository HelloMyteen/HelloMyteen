#pragma once
#ifndef RoomTwo_h
#define RoomTwo_h

#include "cocos2d.h"
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "MapSceneTwo.h"
#include "MutiPlayerMapSelect.h"
#include "extensions/cocos-ext.h"  
#include "Clientin.h"
#include "SelectManager.h"
#include "SocketClient.h"
#include "SocketServer.h"


USING_NS_CC;

class RoomTwo :public cocos2d::Layer
{
public:

	std::string the_ip;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void ButtonToStartGame(cocos2d::Ref* pSender);
	void ButtonBackSelectManager(cocos2d::Ref* pSender);
	void ButtonToMapTwo(cocos2d::Ref* pSender);
	void BackToSelectManager(cocos2d::Ref* pSender);

	void update(float dt);
	void myupdate(float dt);
	CREATE_FUNC(RoomTwo);
};

#endif /* RoomTwo_h */
