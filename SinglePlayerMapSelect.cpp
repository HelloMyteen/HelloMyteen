//
//  SinglePlayerMapSelect.cpp
//  try-mobile
//
//  Created by 叶琪 on 2018/6/22.
//

#include "SinglePlayerMapSelect.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "MapScene.h"
#include "MyScene.h"


USING_NS_CC;
Scene* SinglePlayerMapSelect::createScene()
{
    auto scene = Scene::create();
    auto layer = SinglePlayerMapSelect::create();
    scene->addChild(layer);
    return scene;
}
bool SinglePlayerMapSelect::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//在屏幕最底层添加一层黑幕，用于添加背景
    auto menu = Sprite::create("black.png");
    menu->setPosition(size.width/2,size.height/2);
    menu->setScale(1.0f);
    this->addChild(menu);
    
//  添加经过九宫格算法处理后的背景
    //auto backgroundMapSelect = NinePatch2::createPatch(size.width,size.height, 0, Vec2(0, 0));
	auto backgroundMapSelect = NinePatch2::createPatch(size.width,size.height,0,Vec2(0,0));
    addChild(backgroundMapSelect);
    
    
  
    auto pMapOne = MenuItemImage::create("SelectMapOne.png", "SelectMapOne.png", this, menu_selector(SinglePlayerMapSelect::ButtonToMapScene));
    auto MapOne = Menu::create(pMapOne,  NULL);
    MapOne->setAnchorPoint(Vec2(0,0));
    MapOne->setPosition(size.width/4, size.height/4);
    MapOne->setScale(0.6f);
    this->addChild(MapOne);
    
    auto pMapTwo = MenuItemImage::create("SelectMapOne.png", "SelectMapOne.png", this, menu_selector(SinglePlayerMapSelect::ButtonToMapScene));
    auto MapTwo = Menu::create(pMapTwo,  NULL);
    MapTwo->setAnchorPoint(Vec2(0,0));
    MapTwo->setPosition(size.width-size.width/4, size.height/4);
    MapTwo->setScale(0.6f);
    this->addChild(MapTwo);
    
//     auto pMuti = MenuItemImage::create("MutiPlayer.png", "MutiPlayer.png", this, menu_selector(MyWorld::menuButton012));
//    auto Muti = Menu::create(pMuti,  NULL);
//    Muti->setAnchorPoint(Vec2(0,0));
//    Muti->setPosition(size.width/2, size.height/2);
//    Muti->setScale(0.6f);
//    this->addChild(Muti);
    
    auto pMapSelectReturn = MenuItemImage::create("Return.png", "Return.png", this, menu_selector(SinglePlayerMapSelect::Return));
    auto MapSelectReturn = Menu::create(pMapSelectReturn,  NULL);
    MapSelectReturn->setAnchorPoint(Vec2(0,0));
    MapSelectReturn->setPosition(size.width/2, size.height/2-80);
    MapSelectReturn->setScale(0.6f);
    this->addChild(MapSelectReturn);

//    auto pMenu11 = MenuItemImage::create("button.png", "button.png", this, menu_selector(MyWorld::menuButton012));
//    auto label11 = LabelTTF::create("start", "Arial", 20);
//    auto pLabel11 = MenuItemLabel::create(label11);
//    auto menu11 = Menu::create(pMenu11, pLabel11, NULL);
//    menu11->setPosition(size.width/2, size.height/2);
//        menu11->setScale(0.6f);
//
//    this->addChild(menu11);

    return true;
}
void SinglePlayerMapSelect::ButtonToMapScene(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MapScene::createScene()));
}
void SinglePlayerMapSelect::Return(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MyWorld::createScene()));
}
//void SinglePlayerMapSelect::menuButton012(Ref* pSender)
//{
//    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MapScene::createScene()));
//}



