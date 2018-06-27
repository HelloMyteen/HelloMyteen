#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MyScene.h"
#include "NinePatch.h"

class HelloWorld : public cocos2d::Layer
{
public:
    bool is_paused;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
   
    void menuButton011(cocos2d::Ref* pSender);
  
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void menuMusicCallBack(cocos2d::Ref* pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
