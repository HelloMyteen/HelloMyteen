#ifndef __NINEPATCH_SCENE_H__
#define __NINEPATCH_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;

class NinePatch : public Layer
{
public:
	static NinePatch* createPatch(int width, int height, int borderSize, Point position);
	void initPatch(int width, int height, int borderSize, Point position);
	CREATE_FUNC(NinePatch);
};

class NinePatch1 : public Layer
{
public:
    static NinePatch1* createPatch(int width, int height, int borderSize, Point position);
    void initPatch(int width, int height, int borderSize, Point position);
    CREATE_FUNC(NinePatch1);
};

class NinePatch2 : public Layer
{
public:
    static NinePatch2* createPatch(int width, int height, int borderSize, Point position);
    void initPatch(int width, int height, int borderSize, Point position);
    CREATE_FUNC(NinePatch2);
};
class NinePatch3 : public Layer
{
public:
	static NinePatch3* createPatch(int width, int height, int borderSize, Point position);
	void initPatch(int width, int height, int borderSize, Point position);
	CREATE_FUNC(NinePatch3);
};


#endif

