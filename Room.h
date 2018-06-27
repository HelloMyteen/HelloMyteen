#ifndef Room_h
#define Room_h

#include "cocos2d.h"
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "MutiPlayerMapSelect.h"
#include "extensions/cocos-ext.h"  
#include "Clientin.h"
#include "SelectManager.h"
#include "SocketClient.h"
#include "SocketServer.h"


USING_NS_CC;

class Room :public cocos2d::Layer
{
public:

	std::string the_ip;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void ButtonToStartGame(cocos2d::Ref* pSender);
	void ButtonBackSelectManager(cocos2d::Ref* pSender);
	void ButtonToMap(cocos2d::Ref* pSender);
	void BackToSelectManager(cocos2d::Ref* pSender);

	void update(float dt);
	void myupdate(float dt);
	CREATE_FUNC(Room);
};

#endif /* Room_h */
