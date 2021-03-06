//
//  MapScene.h
//  firstcode-mobile
//
//  Created by 叶琪 on 2018/6/13.
//

#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
#include "MyScene.h"
#include "Moveable.h"
#include "HelloWorldScene.h"
#include "Building.h"
#include "BuildingBase.h"
#include "Player.h"
#include "SocketClient.h"
#include "SocketServer.h"

class MapScene :public cocos2d::Layer
{
private:
	PhysicsBody * physicsBodyD = PhysicsBody::createCircle(50,
		PhysicsMaterial(0.1f, 0.0f, 0.0f));      //创建刚体
	PhysicsBody * physicsBodyFD = PhysicsBody::createCircle(50,
		PhysicsMaterial(0.1f, 0.0f, 0.0f));      //创建刚体
public:
    int chenumber=0;
	float dx=0, dy=0;
    static cocos2d::Scene* createScene();
    virtual bool init();

	TMXTiledMap * map = nullptr;
	void setPhysicD(Sprite * sp);
	void setPhysicFD(Sprite * sp);
    void onTouchesMovedX(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMovedY(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void menuBack(cocos2d::Ref* pSender);
    CREATE_FUNC(MapScene);

	//..................................
	/**************************************************************************************************************/
	std::vector<Moveable *> _moveables;
	std::vector<Building*>_buildings;

	std::vector<Moveable *> _moveablesE;
	std::vector<Building *> _buildingsE;
	/****************************************************************************************************************/

	//创建基地
	BuildingBase * bases[4] = { NULL };
	std::map<BuildingBase*, std::string> _bases;
	
	void prebase();
    //updata
	void update(float dt);     //更新地图信息是否有兵厂等
	void orderupdate(float dt);


   //一下都是陈磊瞎写的
    // OpenGL坐标转成格子坐标
    cocos2d::Vec2 tileCoordForPosition(const cocos2d::Vec2& position, decltype(cocos2d::TMXTiledMap::create("map.tmx")) map)
    {
        cocos2d::Size mapSize = map->getMapSize();
        cocos2d::Size tileSize = map->getTileSize();
		int x = (position.x - dx) / tileSize.width;
		int y = (mapSize.height*tileSize.height - position.y + dy) / tileSize.height;
        return cocos2d::Vec2(x, y);
    }
    // tile坐标转成瓦片格子中心的OpenGL坐标
    cocos2d::Vec2 positionForTileCoord(const cocos2d::Vec2& tileCoord, decltype(cocos2d::TMXTiledMap::create("map.tmx")) map)
    {
        cocos2d::Size mapSize = map->getMapSize();
        cocos2d::Size tileSize = map->getTileSize();
		int x = tileCoord.x * tileSize.width + tileSize.width / 2;
		int y = (mapSize.height - tileCoord.y)*tileSize.height - tileSize.height / 2;
        return cocos2d::Vec2(x, y);
    }

	void changeTank(float dt);
	void changeSoldier(float dt);
	void changeDog(float dt);
	void changeMine(float dt);
	void changePower(float dt);
	void changeCarFac(float dt);
	void changeSoldierFac(float dt);

private:
	cocos2d::Sprite* menuSell;
	cocos2d::Sprite* menuTank;
	cocos2d::Sprite* menuSoldier;
	cocos2d::Sprite* menuDog;
	cocos2d::Sprite* menuMine;
	cocos2d::Sprite* menuPower;
	cocos2d::Sprite* menuCarFac;
	cocos2d::Sprite* menuSoldierFac;

	bool isTank = true;
	bool isSoldier = true;
	bool isDog = true;
	bool isMine = true;
	bool isPower = true;
	bool isCarFac = true;
	bool isSoldierFac = true;
};

#endif /* MapScene_h */
