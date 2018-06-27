//
//  MyScene.cpp
//  firstcode-mobile
//
//  Created by 叶琪 on 2018/5/30.
//

#include "MyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "SinglePlayerMapSelect.h"
#include "SelectManager.h"
USING_NS_CC;
Scene* MyWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = MyWorld::create();
    scene->addChild(layer);
    return scene;
}
bool MyWorld::init()
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
    //auto background1 = NinePatch1::createPatch(size.width,size.height, 0, Vec2(0, 0));
	auto background1 = NinePatch1::createPatch(size.width,size.height,0,Vec2(0,0));
    addChild(background1);
//    
    auto pSingle = MenuItemImage::create("SinglePlayer.png", "SinglePlayer.png", this, menu_selector(MyWorld::ButtonToSinglePlayerMapSelect));
    auto Single = Menu::create(pSingle,  NULL);
    Single->setAnchorPoint(Vec2(0,0));
    Single->setPosition(size.width/2, size.height/2+80);
    Single->setScale(0.6f);
    this->addChild(Single);
    
     auto pMuti = MenuItemImage::create("MutiPlayer.png", "MutiPlayer.png", this, menu_selector(MyWorld::menuButton012));
    auto Muti = Menu::create(pMuti,  NULL);
    Muti->setAnchorPoint(Vec2(0,0));
    Muti->setPosition(size.width/2, size.height/2);
    Muti->setScale(0.6f);
    this->addChild(Muti);
    
    auto pReturn = MenuItemImage::create("Return.png", "Return.png", this, menu_selector(MyWorld::Return));
    auto Return = Menu::create(pReturn,  NULL);
    Return->setAnchorPoint(Vec2(0,0));
    Return->setPosition(size.width/2, size.height/2-80);
    Return->setScale(0.6f);
    this->addChild(Return);

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
void MyWorld::ButtonToSinglePlayerMapSelect(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, SinglePlayerMapSelect::createScene()));
}
void MyWorld::Return(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, HelloWorld::createScene()));
}
void MyWorld::menuButton012(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, SelectManager::createScene()));
}


