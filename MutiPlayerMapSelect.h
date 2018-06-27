//
//  MutiPlayerMapSelect.h
//  try-mobile
//
//  Created by 叶琪 on 2018/6/22.
//

#ifndef MutiPlayerMapSelect_h
#define MutiPlayerMapSelect_h


#include "cocos2d.h"
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "Room.h"
#include "SelectManager.h"
#include "extensions/cocos-ext.h" 
#include <iostream>
#include<vector>


USING_NS_CC;
USING_NS_CC_EXT;

class MutiPlayerMapSelect :public CCLayer,public cocos2d::extension::EditBoxDelegate {
private:
	EditBox * editBoxManagerUsername1;//用户名
	void addEditBox(EditBox * editBox, CCPoint editPoint, char * defaultValue, bool isPassword);//添加输入框    
	bool checkInput();//输入验证
	void toGameScene();//跳转到游戏场景
	void toLoginScene();//跳转到登录场景

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MutiPlayerMapSelect);
	virtual void editBoxEditingDidBegin(extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(extension::EditBox* editBox);
	virtual void editBoxTextChanged(extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(extension::EditBox* editBox);
	void Return(cocos2d::Ref* pSender);
	void ButtonToRoom(cocos2d::Ref* pSender);
	void ButtonToRoomTwo(cocos2d::Ref* pSender);

};




#endif /* MutiPlayerMapSelect_h */
