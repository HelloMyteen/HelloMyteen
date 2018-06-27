//
//  SelectManager.cpp
//  try-mobile
//
//  Created by 叶琪 on 2018/6/23.

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "MapScene.h"
#include "MyScene.h"
#include "SelectManager.h"
#include "cocos2d.h"
#include "order.h"
//std::vector<Player> _players;
//int socketflag = 0;

extern Message message;

USING_NS_CC;
Scene* SelectManager::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectManager::create();
    scene->addChild(layer);
    return scene;
}
bool SelectManager::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	///*this->size1 = CCDirector::sharedDirector()->getVisibleSize();*/
//在屏幕最底层添加一层黑幕，用于添加背景
    auto menu = Sprite::create("black.png");
    menu->setPosition(size.width/2,size.height/2);
    menu->setScale(1.0f);
    this->addChild(menu);
    
//  添加经过九宫格算法处理后的背景
    //auto backgroundSelectManager = NinePatch1::createPatch(size.width,size.height, 0, Vec2(0, 0));
	auto backgroundSelectManager = NinePatch1::createPatch(size.width,size.height,0,Vec2(0,0));
    addChild(backgroundSelectManager);

	///*editBox = cocos2d::extension::EditBox::create(Size(300, 40),Sprite::create("START.png"),Sprite::create("START.png"));editBox->setPosition(Vec2(size.width / 2, size.height / 2));
	//this->addChild(editBox);*/
	//设置预置文本
	////editBox->setPlaceHolder("please input:");

	//设置文本字体的颜色

	////editBox->setFontColor(ccc3(255, 0, 0));

	//设置最大长度 ，按说这个地方是输入框文字的长度，但是在win32上不管用，移植到android的时候是管用的

	////editBox->setMaxLength(1);

	//setInputMode()设置输入类型，可以包括如下的几种
	//   kEditBoxInputModeAny:     开启任何文本的输入键盘,包括换行

	//   kEditBoxInputModeEmailAddr:  开启 邮件地址 输入类型键盘

	//   kEditBoxInputModeNumeric:   开启 数字符号 输入类型键盘

	//   kEditBoxInputModePhoneNumber: 开启 电话号码 输入类型键盘

	//   kEditBoxInputModeUrl:     开启 URL 输入类型键盘

	//   kEditBoxInputModeDecimal:   开启 数字 输入类型键盘，允许小数点

	//   kEditBoxInputModeSingleLine: 开启任何文本的输入键盘,不包括换行
	////editBox->setInputMode(kEditBoxInputModeAny);

	//设置输入标志，可以有如下的几种
	//kEditBoxInputFlagPassword:        密码形式输入

	//kEditBoxInputFlagSensitive:        敏感数据输入、存储输入方案且预测自动完成

	//kEditBoxInputFlagInitialCapsWord:     每个单词首字母大写,并且伴有提示

	//kEditBoxInputFlagInitialCapsSentence:   第一句首字母大写,并且伴有提示

	//kEditBoxInputFlagInitialCapsAllCharacters:所有字符自动大写
	////editBox->setInputFlag(kEditBoxInputFlagPassword);

	//设置键盘中return键显示的字符，这个移植android的时候没有看出来

	////editBox->setReturnType(kKeyboardReturnTypeGo);

	//包括这些选项

	//kKeyboardReturnTypeDefault: 默认使用键盘return 类型

	//kKeyboardReturnTypeDone:   默认使用键盘return类型为“Done”字样

	//kKeyboardReturnTypeSend:   默认使用键盘return类型为“Send”字样

	//kKeyboardReturnTypeSearch:  默认使用键盘return类型为“Search”字样

	//kKeyboardReturnTypeGo:    默认使用键盘return类型为“Go”字样

	//写上这句话的时候以下的四个函数才会被调用
	////editBox->setDelegate(this);
    auto pMapOne = MenuItemImage::create("Manager.png", "Manager.png", this, menu_selector(SelectManager::ButtonToMutiPlayerMapSelect));
    auto MapOne = Menu::create(pMapOne,  NULL);
    MapOne->setAnchorPoint(Vec2(0,0));
    MapOne->setPosition(size.width/4, size.height/4);
    MapOne->setScale(0.6f);
    this->addChild(MapOne);
    
    auto pMapTwo = MenuItemImage::create("Client.png", "Client.png", this, menu_selector(SelectManager::ButtonToInput));
    auto MapTwo = Menu::create(pMapTwo,  NULL);
    MapTwo->setAnchorPoint(Vec2(0,0));
    MapTwo->setPosition(size.width-size.width/4, size.height/4);
	MapTwo->setScale(0.6f);
    this->addChild(MapTwo);


	//string filepath = CCFileUtils::sharedFileUtils()->fullPathForFilename("D:\qwe\proj.win32\Debug.win32\1234.txt");
	
	/*auto filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + "1234.txt";
	auto* readLabel = Label::create("read", "Arial", 56);
	readLabel->setColor(Color3B(0, 0, 0));
	auto* pReadLabel = MenuItemLabel::create(readLabel, this, menu_selector(SelectManager::readCallback));
	auto* buttonReadLabel = Menu::create(pReadLabel, NULL);
	buttonReadLabel->setPosition(320, 260);
	addChild(buttonReadLabel);*/
	
//     auto pMuti = MenuItemImage::create("MutiPlayer.png", "MutiPlayer.png", this, menu_selector(MyWorld::menuButton012));
//    auto Muti = Menu::create(pMuti,  NULL);
//    Muti->setAnchorPoint(Vec2(0,0));
//    Muti->setPosition(size.width/2, size.height/2);
//    Muti->setScale(0.6f);
//    this->addChild(Muti);
    
    auto pSelectManagerReturn = MenuItemImage::create("Return.png", "Return.png", this, menu_selector(SinglePlayerMapSelect::Return));
    auto SelectManagerReturn = Menu::create(pSelectManagerReturn,  NULL);
    SelectManagerReturn->setAnchorPoint(Vec2(0,0));
    SelectManagerReturn->setPosition(size.width/2, size.height/2-80);
    SelectManagerReturn->setScale(0.6f);
    this->addChild(SelectManagerReturn);
	log(1);

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
void SelectManager::ButtonToMutiPlayerMapSelect(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MutiPlayerMapSelect::createScene()));
}
void SelectManager::Return(Ref* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MyWorld::createScene()));
}

void SelectManager::ButtonToInput(Ref* pSender)
{
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, RegisterHandleLayer::createScene()));
}
//void SelectManager::readCallback(Ref* pSender)
//{
//
//	std::string path = FileUtils::sharedFileUtils()->getWritablePath() + "D:\qwe\test.txt";
//	FILE* file = fopen(path.c_str(), "rt");
//	fputs("1234234", file);
//}
//void SinglePlayerMapSelect::menuButton012(Ref* pSender)
//{
//    Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MapScene::createScene()));
//}



//void EditBoxManager::editBoxEditingDidBegin(EditBox* editBox){
//    log("click");
//}
//void EditBoxManager::editBoxEditingDidEnd(EditBox* editBox){
//    log("leave click");
//}
//void EditBoxManager::editBoxTextChanged(EditBox* editBox, const std::string& text){
//    log("text change=%s", text.c_str());
//}
//void EditBoxManager::editBoxReturn(EditBox* editBox){
//    log("returned");
//}





//void SelectManager::editBoxEditingDidBegin(EditBox * editBox)
//{
//	log("begin!");
//	LabelTTF * ttf = LabelTTF::create("begin", "", 24);
//	ttf->setPosition(ccp(size1.width / 4, size1.height * 1 / 5));
//	addChild(ttf);
//}
//
//void SelectManager::editBoxEditingDidEnd(EditBox * editBox)
//{
//	log("end!");
//	LabelTTF * ttf = LabelTTF::create("end", "", 24);
//	ttf->setPosition(ccp(size1.width / 4, size1.height * 4 / 5));
//	addChild(ttf);
//}
//
//void SelectManager::editBoxTextChanged(EditBox * editBox, const std::string & text)
//{
//	log("textChanged!");
//	LabelTTF * ttf = LabelTTF::create("textChanged!", "", 24);
//	ttf->setPosition(ccp(size1.width / 4 , size1.height * 3 / 5));
//	addChild(ttf);
//}
//
//void SelectManager::editBoxReturn(EditBox * editBox)
//{
//	log("return");
//	LabelTTF * ttf = LabelTTF::create("return", "", 24);
//	ttf->setPosition(Vec2(size1.width / 4, size1.height * 2 / 5));
//	addChild(ttf);
//	char * str = (char *)this->editBox->getText();
//	LabelTTF * text = LabelTTF::create(str, "", 24);
//	text->setPosition(ccp(size1.width / 2, size1.height * 2 / 5));
//	addChild(text);
//}