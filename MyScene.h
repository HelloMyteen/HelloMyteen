//
//  MyScene.h
//  firstcode
//
//  Created by 叶琪 on 2018/5/30.
//
#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "SinglePlayerMapSelect.h"
#include "SelectManager.h"
class MyWorld :public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
      void ButtonToSinglePlayerMapSelect(cocos2d::Ref* pSender);
      void menuButton012(cocos2d::Ref* pSender);
      void Return(cocos2d::Ref* pSender);
    CREATE_FUNC(MyWorld);
};
#endif

