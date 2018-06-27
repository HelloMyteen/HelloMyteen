//
//  Toast.h
//  experiment
//
//  Created by 叶琪 on 2018/6/24.
//

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Toast : public Layer {
public:
    Toast();
    ~Toast();
    virtual bool init();
    CREATE_FUNC(Toast);
    static Toast* create(const char* text, int fontsize = 30, float time = 1);
private:
    //设置文字
    void setText(const char* text, int fontsize, float time);
    //设置背景
    void setBackgound();
    //删除
    void removeSelf();
private:
    LayerColor *m_backgound;
    Label *m_label;
};
