#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "NinePatch.h"
#include "MapScene.h"
#include "MyScene.h"
#include "SelectManager.h"
#include "cocos2d.h"
#include "Clientin.h"
#include "order.h"

extern Message message;

Scene* RegisterHandleLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = RegisterHandleLayer::create();
	scene->addChild(layer);
	return scene;
}

bool RegisterHandleLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	//精灵帧缓存
	cocos2d::SpriteFrameCache * sfCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	sfCache->addSpriteFramesWithFile("p_register.plist");

	//屏幕尺寸
	cocos2d::Size size = Director::sharedDirector()->getWinSize();

	////注册框
	cocos2d::SpriteFrame * f_register_box = sfCache->spriteFrameByName("1.png");
	cocos2d::Sprite * spriteBox = cocos2d::Sprite::createWithSpriteFrame(f_register_box);
	spriteBox->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(spriteBox);

	//注册框尺寸
	CCSize boxSize = spriteBox->getContentSize();

	//ID
	CCSpriteFrame * f_register_username = sfCache->spriteFrameByName("2.png");
	CCSprite * spriteUsername = CCSprite::createWithSpriteFrame(f_register_username);
	CCSize spriteUsernameSize = spriteUsername->getContentSize();
	CCSize editSize = CCSizeMake(spriteUsernameSize.width * 3 / 5, spriteUsernameSize.height);
	CCPoint spriteUsernamePoint = CCPointMake(size.width / 2, size.height / 2 + spriteUsernameSize.height * 11 / 6);
	spriteUsername->setPosition(spriteUsernamePoint);
	this->addChild(spriteUsername);

	//IP
	CCSpriteFrame * f_register_password = sfCache->spriteFrameByName("3.png");
	CCSprite * spritePassword = CCSprite::createWithSpriteFrame(f_register_password);
	CCSize spritePasswordSize = spritePassword->getContentSize();
	CCPoint spritePasswordPoint = CCPointMake(size.width / 2, size.height / 2 + spritePasswordSize.height / 2);
     spritePassword->setPosition(spritePasswordPoint);
	this->addChild(spritePassword);

	//重复密码
	/*CCSpriteFrame * f_register_repassword = sfCache->spriteFrameByName("4.png");
	CCSprite * spriteRePassword = CCSprite::createWithSpriteFrame(f_register_repassword);
	CCPoint spriteRePasswordPoint = CCPointMake(size.width / 2, size.height / 2 - spriteUsernameSize.height * 5 / 6);
	spriteRePassword->setPosition(spriteRePasswordPoint);
	this->addChild(spriteRePassword);*/

	//添加输入框
	editBoxUsername = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("2.png"));
	editBoxUsername->setPosition(Vec2(size.width / 2, size.height * 3 / 4));
	editBoxUsername->setFontColor(Color3B(0, 255, 0));
	editBoxUsername->setPlaceHolder("Please input your ID");
	editBoxUsername->setMaxLength(20);
	addChild(editBoxUsername);

	editBoxPassword = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("3.png"));
	editBoxPassword->setPosition(Vec2(size.width / 2, size.height *9/16));
	editBoxPassword->setFontColor(Color3B(0, 255, 0));
	editBoxPassword->setPlaceHolder("Please input your IP");
	editBoxPassword->setMaxLength(20);
	addChild(editBoxPassword);
	/*editBoxPassword = CCEditBox::create(editSize, Sprite::create());
	addEditBox(editBoxPassword, spritePasswordPoint, "创建密码", true);
	editBoxRePassword = CCEditBox::create(editSize, Sprite::create());
	addEditBox(editBoxRePassword, spriteRePasswordPoint, "重复密码", true);
*/
	////注册按钮
	//CCSpriteFrame * f_register_btn_register = sfCache->spriteFrameByName("button.png");
	//CCSprite * sprite_register_btn_register = CCSprite::createWithSpriteFrame(f_register_btn_register);

	//cocos2d::SpriteFrame * f_register_btn_register_select = sfCache->spriteFrameByName("button.png");
	//cocos2d::Sprite * sprite_register_btn_register_select = CCSprite::createWithSpriteFrame(f_register_btn_register_select);

	//CCMenuItemSprite * itemRegister = CCMenuItemSprite::create(
	//	sprite_register_btn_register,
	//	sprite_register_btn_register_select,
	//	this,
	//	menu_selector(RegisterHandleLayer::Button));
	//CCSize registerBthSize = itemRegister->getContentSize();
	//itemRegister->setPosition(CCPointMake(size.width / 2 - boxSize.width / 4,
	//	size.height / 2 - boxSize.height / 2 + registerBthSize.height * 2));

	
	////按钮菜单
	//CCMenu * menu = CCMenu::create(itemRegister, itemLogin, NULL);
	//menu->setPosition(CCPointZero);
	//this->addChild(menu);
	auto pClientButtonBack = MenuItemImage::create("5.png", "5.png", this, menu_selector(RegisterHandleLayer::ClientButtonBack));
	auto ClientButtonBack = Menu::create(pClientButtonBack, NULL);
	ClientButtonBack->setAnchorPoint(Vec2(0.5, 0.5));
	ClientButtonBack->setPosition(size.width / 2, size.height * 3 / 16 );
	this->addChild(ClientButtonBack);
	

	auto pButtonToRoom = MenuItemImage::create("4.png", "4.png", this, menu_selector(RegisterHandleLayer::ButtonToRoom));
	auto ButtonToRoom = Menu::create(pButtonToRoom, NULL);
	ButtonToRoom->setAnchorPoint(Vec2(0.5, 0.5));
	ButtonToRoom->setPosition(size.width / 2, size.height * 3 / 8);
	this->addChild(ButtonToRoom);
	return true;
}
//键盘弹出后输入框获得焦点时触发
void RegisterHandleLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox *editBox)
{
	log("begin");
}

//键盘隐藏后输入框失去焦点时触发
void RegisterHandleLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox *editBox)
{
	log("end");
}

//输入框内文本变化时触发
void RegisterHandleLayer::editBoxTextChanged(cocos2d::extension::EditBox *editBox, const std::string &text)
{
	log("change");
}

//按下返回键或点击键盘外的位置时触发（点击当前输入框时不触发）
void RegisterHandleLayer::editBoxReturn(extension::EditBox *editBox)
{
	log("return");
}
void RegisterHandleLayer::addEditBox(EditBox * editBox, CCPoint editPoint, char * defaultValue, bool isPassword)
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

void RegisterHandleLayer::ClientButtonBack(Ref* pSender)
{
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, SelectManager::createScene()));
}
void RegisterHandleLayer::ButtonToRoom(Ref* pSender)
{
	message.ip = editBoxPassword->getText();
	Player myplayer;
	myplayer.setPlayerName(editBoxUsername->getText());
	myplayer.flag = 0;
	message._players.push_back(myplayer);
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, Room::createScene()));
}