#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "SimpleAudioEngine.h"
#include "order.h"
USING_NS_CC;

using namespace cocostudio::timeline;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
// 获取屏幕大小
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//加载九宫格算法处理后的背景
    //auto background = NinePatch::createPatch(size.width,size.height, 0, Vec2(0, 0));
	auto background = NinePatch::createPatch(size.width,size.height,0,Vec2(0,0));
    addChild(background);
    
//添加“开始游戏”按钮，点击进入游戏界面
    auto pMenu11 = MenuItemImage::create("START.png", "START.png", this, menu_selector(HelloWorld::menuButton011));
    auto menu11 = Menu::create(pMenu11,  NULL);
    menu11->setAnchorPoint(Vec2(0,0));
    menu11->setPosition(size.width/2, size.height/2);
    menu11->setScale(0.6f);
    this->addChild(menu11);
    
//添加“退出游戏”，点击结束游戏
    auto pQuit = MenuItemImage::create("QUIT.png","QUIT.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    auto quit = Menu::create(pQuit,  NULL);
    quit->setAnchorPoint(Vec2(0,0));
    quit->setPosition(size.width/2, size.height / 2 - 80);
    quit->setScale(0.6f);
    this->addChild(quit);
    
//载入背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Victory.mp3", true);
    is_paused = false;
    
//添加音乐的“播放”和“暂停”键
    auto music_button = MenuItemImage::create("Play.png", "Pause.png");
    auto pause_button = MenuItemImage::create("Pause.png","Play.png");

//设置“播放”和“暂停”之间的转换
    MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::menuMusicCallBack, this), music_button, pause_button, NULL);
    toggleItem->setScale(1.0f);
    toggleItem->setPosition(size.width-27,size.height-27);
    auto menu = Menu::create(toggleItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    return true;
}

//界面转化
void HelloWorld::menuButton011(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MyWorld::createScene()));
}
//退出程序
//void HelloWorld::menuCloseCallback(Ref* pSender)
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif
    Director::getInstance()->end();
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//音乐播放
void HelloWorld::menuMusicCallBack(cocos2d::Ref* pSender)
{
    
    if (is_paused == false)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        is_paused = true;
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        is_paused = false;
    }
}

