//
//  SinglePlayerMapSelect.h
//  try-mobile
//
//  Created by 叶琪 on 2018/6/22.
//

#ifndef SinglePlayerMapSelect_h
#define SinglePlayerMapSelect_h

#include "cocos2d.h"
#include "MyScene.h"
#include "HelloWorldScene.h"
#include "MapScene.h"

class SinglePlayerMapSelect :public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Return(cocos2d::Ref* pSender);
    void ButtonToMapScene(cocos2d::Ref* pSender);
    void ButtonToMapSceneTwo(cocos2d::Ref* pSender);
//    void menuBack(cocos2d::Ref* pSender);
    CREATE_FUNC(SinglePlayerMapSelect);
    

};



#endif /* SinglePlayerMapSelect_h */
