//
//  SelectManager.h
//  try-mobile
//
//  Created by 叶琪 on 2018/6/23.
//

#ifndef SelectManager_h
#define SelectManager_h

#include "cocos2d.h"
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "MutiPlayerMapSelect.h"
#include "extensions/cocos-ext.h"  
#include "Clientin.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SelectManager :public cocos2d::Layer
	/*,public cocos2d::extension::EditBoxDelegate*/
{
public:

    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Return(cocos2d::Ref* pSender);
    void ButtonToMutiPlayerMapSelect(cocos2d::Ref* pSender);
	void ButtonToInput(cocos2d::Ref* pSender);
	/*void readCallback(cocos2d::Ref* pSender);
	void saveCallback(cocos2d::Ref* pSender);*/
//
//	//当编辑框获得焦点时将被调用
//	void editBoxEditingDidBegin(cocos2d::Ref* editBox);
//	//当编辑框失去焦点后将被调用
//	void editBoxEditingDidEnd(cocos2d::Ref* editBox);
//	//当编辑框内容发生改变将被调用
//	void editBoxTextChanged(cocos2d::Ref* editBox, const std::string& text);
//	//当编辑框的结束操作被调用
//	void editBoxReturn(cocos2d::Ref* editBox);
//private:
//	cocos2d::extension::EditBox * editBox;
//	cocos2d::Size size1;
	CREATE_FUNC(SelectManager);
    };

#endif /* SelectManager_h */