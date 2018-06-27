#ifndef __MyGame__RegisterHandleLayer__
#define __MyGame__RegisterHandleLayer__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h" 
#include "SelectManager.h"
#include "Room.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RegisterHandleLayer :public CCLayer, public cocos2d::extension::EditBoxDelegate {
private:
	EditBox * editBoxUsername;//用户名
	EditBox * editBoxPassword;//密码
	EditBox * editBoxRePassword;//重复密码
	void addEditBox(EditBox * editBox, CCPoint editPoint, char * defaultValue, bool isPassword);//添加输入框    
	bool checkInput();//输入验证
	void toGameScene();//跳转到游戏场景
	void toLoginScene();//跳转到登录场景

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RegisterHandleLayer);
	virtual void editBoxEditingDidBegin(extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(extension::EditBox* editBox);
	virtual void editBoxTextChanged(extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(extension::EditBox* editBox);
	void ButtonToRoom(cocos2d::Ref* pSender);
	void ClientButtonBack(cocos2d::Ref* pSender);

	
};
#endif /* defined(__MyGame__RegisterHandleLayer__) */gma once
