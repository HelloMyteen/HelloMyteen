//
//  MutiPlayerMapSelect.cpp
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
#include "MutiPlayerMapSelect.h"
#include "SelectManager.h"
#include "order.h"

extern Message message;

USING_NS_CC;
Scene* MutiPlayerMapSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = MutiPlayerMapSelect::create();
	scene->addChild(layer);
	return scene;
}
bool MutiPlayerMapSelect::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Player _myplayer;
	
	//精灵帧缓存
	cocos2d::SpriteFrameCache * sfCache1 = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	sfCache1->addSpriteFramesWithFile("p_register1.plist");

	//屏幕尺寸
	cocos2d::Size size1 = Director::sharedDirector()->getWinSize();

	cocos2d::SpriteFrame * f_register_box1 = sfCache1->spriteFrameByName("MapSelect.png");
	cocos2d::Sprite * spriteBox1 = cocos2d::Sprite::createWithSpriteFrame(f_register_box1);
	spriteBox1->setPosition(Vec2(size1.width / 2, size1.height / 2));
	this->addChild(spriteBox1);
	
	//注册框尺寸
	CCSize boxSize1 = spriteBox1->getContentSize();

	//ID
	CCSpriteFrame * f_register_username1 = sfCache1->spriteFrameByName("ID.png");
	CCSprite * spriteUsername1 = CCSprite::createWithSpriteFrame(f_register_username1);
	CCSize spriteUsernameSize1 = spriteUsername1->getContentSize();
	CCSize editSize = CCSizeMake(spriteUsernameSize1.width * 3 / 5, spriteUsernameSize1.height);
	CCPoint spriteUsernamePoint1 = CCPointMake(size1.width / 2, size1.height / 2 + spriteUsernameSize1.height * 11 / 6);
	spriteUsername1->setPosition(spriteUsernamePoint1);
	this->addChild(spriteUsername1);

	
	

	//添加输入框
	editBoxManagerUsername1 = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("2.png"));
	editBoxManagerUsername1->setPosition(Vec2(size1.width / 2, size1.height * 3 / 4));
	editBoxManagerUsername1->setFontColor(Color3B(0, 255, 0));
	editBoxManagerUsername1->setPlaceHolder("Please input your ID");
	editBoxManagerUsername1->setMaxLength(20);
	addChild(editBoxManagerUsername1);



	auto pMuti = MenuItemImage::create("SelectMapOne.png", "SelectMapOne.png", this, menu_selector(MutiPlayerMapSelect::ButtonToRoom));
	auto Muti = Menu::create(pMuti, NULL);
	Muti->setAnchorPoint(Vec2(0, 0));
	Muti->setPosition(size.width / 4, size.height / 4);
	Muti->setScale(0.6f);
	this->addChild(Muti);

	

	//     auto pMuti = MenuItemImage::create("MutiPlayer.png", "MutiPlayer.png", this, menu_selector(MyWorld::menuButton012));
	//    auto Muti = Menu::create(pMuti,  NULL);
	//    Muti->setAnchorPoint(Vec2(0,0));
	//    Muti->setPosition(size.width/2, size.height/2);
	//    Muti->setScale(0.6f);
	//    this->addChild(Muti);

	auto pMutiSelectReturn = MenuItemImage::create("Return.png", "Return.png", this, menu_selector(MutiPlayerMapSelect::Return));
	auto MutiSelectReturn = Menu::create(pMutiSelectReturn, NULL);
	MutiSelectReturn->setAnchorPoint(Vec2(0, 0));
	MutiSelectReturn->setPosition(size.width / 2, 40);
	MutiSelectReturn->setScale(0.6f);
	this->addChild(MutiSelectReturn);

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
void MutiPlayerMapSelect::ButtonToRoom(Ref* pSender)
{
	Player myplayer;
	myplayer.setPlayerName(editBoxManagerUsername1->getText());
	myplayer.flag = 1;
	message._players.push_back(myplayer);
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, Room::createScene()));
}
void MutiPlayerMapSelect::Return(Ref* pSender)
{
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, SelectManager::createScene()));
}
//键盘弹出后输入框获得焦点时触发
void MutiPlayerMapSelect::editBoxEditingDidBegin(cocos2d::extension::EditBox *editBox)
{
	log("begin");
}

//键盘隐藏后输入框失去焦点时触发
void MutiPlayerMapSelect::editBoxEditingDidEnd(cocos2d::extension::EditBox *editBox)
{
	log("end");
}

//输入框内文本变化时触发
void MutiPlayerMapSelect::editBoxTextChanged(cocos2d::extension::EditBox *editBox, const std::string &text)
{
	log("change");
}

//按下返回键或点击键盘外的位置时触发（点击当前输入框时不触发）
void MutiPlayerMapSelect::editBoxReturn(extension::EditBox *editBox)
{
	log("%s",editBox->getText());
}
void MutiPlayerMapSelect::addEditBox(EditBox * editBox, CCPoint editPoint, char * defaultValue, bool isPassword)
{
	editBox->CCNode::setPosition(editPoint.x, editPoint.y); //位置
	editBox->setFontColor(Color4B::WHITE); //文字颜色
	editBox->setPlaceHolder(defaultValue); //输入框缺省文字
	editBox->setPlaceholderFontColor(Color4B::WHITE); //缺省文字颜色
	editBox->setMaxLength(20); //最大长度
							   //editBox->setReturnType(kKeyboardReturnTypeDone); //默认使用键盘return类型为Done
							   //editBox->setInputMode(kEditBoxInputModeEmailAddr); //输入键盘模式
							   //if (isPassword) {
							   //	editBox->setInputFlag(kEditBoxInputFlagPassword); //输入密码时的替代符
							   //}
	editBox->setDelegate(this); //设置委托代理对象为当前类
	this->addChild(editBox);
}
enum KeyboardReturnType {
	kKeyboardReturnTypeDefault = 0,
	kKeyboardReturnTypeDone,
	kKeyboardReturnTypeSend,
	kKeyboardReturnTypeSearch,
	kKeyboardReturnTypeGo
};


/**
* \brief The EditBoxInputMode defines the type of text that the user is allowed
* to enter.
*/
enum EditBoxInputMode
{
	/**
	* The user is allowed to enter any text, including line breaks.
	*/
	kEditBoxInputModeAny = 0,

	/**
	* The user is allowed to enter an e-mail address.
	*/
	kEditBoxInputModeEmailAddr,

	/**
	* The user is allowed to enter an integer value.
	*/
	kEditBoxInputModeNumeric,

	/**
	* The user is allowed to enter a phone number.
	*/
	kEditBoxInputModePhoneNumber,

	/**
	* The user is allowed to enter a URL.
	*/
	kEditBoxInputModeUrl,

	/**
	* The user is allowed to enter a real number value.
	* This extends kEditBoxInputModeNumeric by allowing a decimal point.
	*/
	kEditBoxInputModeDecimal,

	/**
	* The user is allowed to enter any text, except for line breaks.
	*/
	kEditBoxInputModeSingleLine
};

/**
* \brief The EditBoxInputFlag defines how the input text is displayed/formatted.
*/
enum EditBoxInputFlag
{
	/**
	* Indicates that the text entered is confidential data that should be
	* obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
	*/
	kEditBoxInputFlagPassword = 0,

	/**
	* Indicates that the text entered is sensitive data that the
	* implementation must never store into a dictionary or table for use
	* in predictive, auto-completing, or other accelerated input schemes.
	* A credit card number is an example of sensitive data.
	*/
	kEditBoxInputFlagSensitive,

	/**
	* This flag is a hint to the implementation that during text editing,
	* the initial letter of each word should be capitalized.
	*/
	kEditBoxInputFlagInitialCapsWord,

	/**
	* This flag is a hint to the implementation that during text editing,
	* the initial letter of each sentence should be capitalized.
	*/
	kEditBoxInputFlagInitialCapsSentence,

	/**
	* Capitalize all characters automatically.
	*/
	kEditBoxInputFlagInitialCapsAllCharacters

};
