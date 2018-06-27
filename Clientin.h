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
	EditBox * editBoxUsername;//�û���
	EditBox * editBoxPassword;//����
	EditBox * editBoxRePassword;//�ظ�����
	void addEditBox(EditBox * editBox, CCPoint editPoint, char * defaultValue, bool isPassword);//��������    
	bool checkInput();//������֤
	void toGameScene();//��ת����Ϸ����
	void toLoginScene();//��ת����¼����

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
