#include "NinePatch.h"
USING_NS_CC;
#define PATCH_WIDTH 968
#define PATCH_HEIGHT 539
#define PATCH_WIDTH1 534
#define PATCH_HEIGHT1 300
#define PATCH_WIDTH2 720
#define PATCH_HEIGHT2 404
#define PATCH_WIDTH3 1024
#define PATCH_HEIGHT3 600

NinePatch* NinePatch::createPatch(int width, int height, int borderSize, Point position)
{
	NinePatch* patch = NinePatch::create();
	if (patch)
	{
		patch->initPatch(width, height, borderSize, position);
		return patch;
	}
	CC_SAFE_DELETE(patch);
	return NULL;
}

NinePatch1* NinePatch1::createPatch(int width, int height, int borderSize, Point position)
{
    NinePatch1* patch = NinePatch1::create();
    if (patch)
    {
        patch->initPatch(width, height, borderSize, position);
        return patch;
    }
    CC_SAFE_DELETE(patch);
    return NULL;
}

NinePatch2* NinePatch2::createPatch(int width, int height, int borderSize, Point position)
{
    NinePatch2* patch = NinePatch2::create();
    if (patch)
    {
        patch->initPatch(width, height, borderSize, position);
        return patch;
    }
    CC_SAFE_DELETE(patch);
    return NULL;
}
NinePatch3* NinePatch3::createPatch(int width, int height, int borderSize, Point position)
{
	NinePatch3* patch = NinePatch3::create();
	if (patch)
	{
		patch->initPatch(width, height, borderSize, position);
		return patch;
	}
	CC_SAFE_DELETE(patch);
	return NULL;
}
void NinePatch::initPatch(int width, int height, int borderSize, Point position)
{
	
	auto* patch1 = Sprite::create("background.png", Rect(0, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch1->setAnchorPoint(Vec2(0, 0));
	patch1->setPosition(position.x, position.y + height - borderSize);
	addChild(patch1);
    
	auto* patch3 = Sprite::create("background.png", Rect(0, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch3->setAnchorPoint(Vec2(0, 0));
	patch3->setPosition(position.x + width - borderSize, position.y + height - borderSize);
	addChild(patch3);
	
	auto* patch7 = Sprite::create("background.png", Rect(0, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch7->setAnchorPoint(Vec2(0, 0));
	patch7->setPosition(position.x, position.y);
	addChild(patch7);
	
	auto* patch9 = Sprite::create("background.png", Rect(PATCH_WIDTH - borderSize, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch9->setAnchorPoint(Vec2(0, 0));
	patch9->setPosition(position.x + width - borderSize, position.y);
	addChild(patch9);
	
	auto* patch2 = Sprite::create("background.png", Rect(borderSize, 0, PATCH_WIDTH - borderSize * 2, borderSize));
	patch2->setAnchorPoint(Vec2(0, 0));
	patch2->setPosition(position.x + borderSize, position.y + height - borderSize);
	patch2->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2));
	addChild(patch2);
	
	auto* patch4 = Sprite::create("background.png", Rect(0, borderSize, borderSize, PATCH_HEIGHT - borderSize * 2));
	patch4->setAnchorPoint(Vec2(0, 0));
	patch4->setPosition(position.x, position.y + borderSize);
	patch4->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch4);

	auto* patch6 = Sprite::create("background.png", Rect(PATCH_HEIGHT - borderSize, borderSize, borderSize, PATCH_HEIGHT - borderSize * 2));
	patch6->setAnchorPoint(Vec2(0, 0));
	patch6->setPosition(position.x + width - borderSize, position.y + borderSize);
	patch6->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch6);

	auto* patch8 = Sprite::create("background.png", Rect(borderSize, PATCH_HEIGHT - borderSize, PATCH_WIDTH - borderSize * 2, borderSize));
	patch8->setAnchorPoint(Vec2(0, 0));
	patch8->setPosition(position.x + borderSize, position.y);
	patch8->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2));
	addChild(patch8);

	auto* patch5 = Sprite::create("background.png", Rect(borderSize, borderSize, PATCH_WIDTH - borderSize*2, PATCH_HEIGHT - borderSize*2));
	patch5->setAnchorPoint(Vec2(0, 0));
	patch5->setPosition(position.x + borderSize, position.y + borderSize);
	patch5->setScale((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2), (float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch5);
}



void NinePatch1::initPatch(int width, int height, int borderSize, Point position)
{
    
    auto* patch1 = Sprite::create("background1.png", Rect(0, PATCH_HEIGHT1 - borderSize, borderSize, borderSize));
    patch1->setAnchorPoint(Vec2(0, 0));
    patch1->setPosition(position.x, position.y + height - borderSize);
    addChild(patch1);
    
    auto* patch3 = Sprite::create("background1.png", Rect(0, PATCH_HEIGHT1 - borderSize, borderSize, borderSize));
    patch3->setAnchorPoint(Vec2(0, 0));
    patch3->setPosition(position.x + width - borderSize, position.y + height - borderSize);
    addChild(patch3);
    
    auto* patch7 = Sprite::create("background1.png", Rect(0, PATCH_HEIGHT1 - borderSize, borderSize, borderSize));
    patch7->setAnchorPoint(Vec2(0, 0));
    patch7->setPosition(position.x, position.y);
    addChild(patch7);
    
    auto* patch9 = Sprite::create("background1.png", Rect(PATCH_WIDTH1 - borderSize, PATCH_HEIGHT1 - borderSize, borderSize, borderSize));
    patch9->setAnchorPoint(Vec2(0, 0));
    patch9->setPosition(position.x + width - borderSize, position.y);
    addChild(patch9);
    
    auto* patch2 = Sprite::create("background1.png", Rect(borderSize, 0, PATCH_WIDTH1 - borderSize * 2, borderSize));
    patch2->setAnchorPoint(Vec2(0, 0));
    patch2->setPosition(position.x + borderSize, position.y + height - borderSize);
    patch2->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH1 - borderSize * 2));
    addChild(patch2);
    
    auto* patch4 = Sprite::create("background1.png", Rect(0, borderSize, borderSize, PATCH_HEIGHT1 - borderSize * 2));
    patch4->setAnchorPoint(Vec2(0, 0));
    patch4->setPosition(position.x, position.y + borderSize);
    patch4->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT1 - borderSize * 2));
    addChild(patch4);

    auto* patch6 = Sprite::create("background1.png", Rect(PATCH_HEIGHT1 - borderSize, borderSize, borderSize, PATCH_HEIGHT1 - borderSize * 2));
    patch6->setAnchorPoint(Vec2(0, 0));
    patch6->setPosition(position.x + width - borderSize, position.y + borderSize);
    patch6->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT1 - borderSize * 2));
    addChild(patch6);

    auto* patch8 = Sprite::create("background1.png", Rect(borderSize, PATCH_HEIGHT1 - borderSize, PATCH_WIDTH1 - borderSize * 2, borderSize));
    patch8->setAnchorPoint(Vec2(0, 0));
    patch8->setPosition(position.x + borderSize, position.y);
    patch8->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH1 - borderSize * 2));
    addChild(patch8);

    auto* patch5 = Sprite::create("background1.png", Rect(borderSize, borderSize, PATCH_WIDTH1 - borderSize*2, PATCH_HEIGHT1 - borderSize*2));
    patch5->setAnchorPoint(Vec2(0, 0));
    patch5->setPosition(position.x + borderSize, position.y + borderSize);
    patch5->setScale((float)(width - borderSize * 2) / (PATCH_WIDTH1 - borderSize * 2), (float)(height - borderSize * 2) / (PATCH_HEIGHT1 - borderSize * 2));
    addChild(patch5);
}

void NinePatch2::initPatch(int width, int height, int borderSize, Point position)
{
    
    auto* patch1 = Sprite::create("MapSelect.png", Rect(0, PATCH_HEIGHT2 - borderSize, borderSize, borderSize));
    patch1->setAnchorPoint(Vec2(0, 0));
    patch1->setPosition(position.x, position.y + height - borderSize);
    addChild(patch1);
    
    auto* patch3 = Sprite::create("MapSelect.png", Rect(0, PATCH_HEIGHT2 - borderSize, borderSize, borderSize));
    patch3->setAnchorPoint(Vec2(0, 0));
    patch3->setPosition(position.x + width - borderSize, position.y + height - borderSize);
    addChild(patch3);
    
    auto* patch7 = Sprite::create("MapSelect.png", Rect(0, PATCH_HEIGHT2 - borderSize, borderSize, borderSize));
    patch7->setAnchorPoint(Vec2(0, 0));
    patch7->setPosition(position.x, position.y);
    addChild(patch7);
    
    auto* patch9 = Sprite::create("MapSelect.png", Rect(PATCH_WIDTH2 - borderSize, PATCH_HEIGHT2 - borderSize, borderSize, borderSize));
    patch9->setAnchorPoint(Vec2(0, 0));
    patch9->setPosition(position.x + width - borderSize, position.y);
    addChild(patch9);
    
    auto* patch2 = Sprite::create("MapSelect.png", Rect(borderSize, 0, PATCH_WIDTH2 - borderSize * 2, borderSize));
    patch2->setAnchorPoint(Vec2(0, 0));
    patch2->setPosition(position.x + borderSize, position.y + height - borderSize);
    patch2->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH2 - borderSize * 2));
    addChild(patch2);
    
    auto* patch4 = Sprite::create("MapSelect.png", Rect(0, borderSize, borderSize, PATCH_HEIGHT2 - borderSize * 2));
    patch4->setAnchorPoint(Vec2(0, 0));
    patch4->setPosition(position.x, position.y + borderSize);
    patch4->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT2 - borderSize * 2));
    addChild(patch4);

    auto* patch6 = Sprite::create("MapSelect.png", Rect(PATCH_HEIGHT2 - borderSize, borderSize, borderSize, PATCH_HEIGHT2 - borderSize * 2));
    patch6->setAnchorPoint(Vec2(0, 0));
    patch6->setPosition(position.x + width - borderSize, position.y + borderSize);
    patch6->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT2 - borderSize * 2));
    addChild(patch6);

    auto* patch8 = Sprite::create("MapSelect.png", Rect(borderSize, PATCH_HEIGHT2 - borderSize, PATCH_WIDTH2 - borderSize * 2, borderSize));
    patch8->setAnchorPoint(Vec2(0, 0));
    patch8->setPosition(position.x + borderSize, position.y);
    patch8->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH2 - borderSize * 2));
    addChild(patch8);

    auto* patch5 = Sprite::create("MapSelect.png", Rect(borderSize, borderSize, PATCH_WIDTH2 - borderSize*2, PATCH_HEIGHT2 - borderSize*2));
    patch5->setAnchorPoint(Vec2(0, 0));
    patch5->setPosition(position.x + borderSize, position.y + borderSize);
    patch5->setScale((float)(width - borderSize * 2) / (PATCH_WIDTH2 - borderSize * 2), (float)(height - borderSize * 2) / (PATCH_HEIGHT2 - borderSize * 2));
    addChild(patch5);
}

void NinePatch3::initPatch(int width, int height, int borderSize, Point position)
{

	auto* patch1 = Sprite::create("RoomBackground.png", Rect(0, PATCH_HEIGHT3 - borderSize, borderSize, borderSize));
	patch1->setAnchorPoint(Vec2(0, 0));
	patch1->setPosition(position.x, position.y + height - borderSize);
	addChild(patch1);

	auto* patch3 = Sprite::create("RoomBackground.png", Rect(0, PATCH_HEIGHT3 - borderSize, borderSize, borderSize));
	patch3->setAnchorPoint(Vec2(0, 0));
	patch3->setPosition(position.x + width - borderSize, position.y + height - borderSize);
	addChild(patch3);

	auto* patch7 = Sprite::create("RoomBackground.png", Rect(0, PATCH_HEIGHT3 - borderSize, borderSize, borderSize));
	patch7->setAnchorPoint(Vec2(0, 0));
	patch7->setPosition(position.x, position.y);
	addChild(patch7);

	auto* patch9 = Sprite::create("RoomBackground.png", Rect(PATCH_WIDTH3 - borderSize, PATCH_HEIGHT3 - borderSize, borderSize, borderSize));
	patch9->setAnchorPoint(Vec2(0, 0));
	patch9->setPosition(position.x + width - borderSize, position.y);
	addChild(patch9);

	auto* patch2 = Sprite::create("RoomBackground.png", Rect(borderSize, 0, PATCH_WIDTH3 - borderSize * 2, borderSize));
	patch2->setAnchorPoint(Vec2(0, 0));
	patch2->setPosition(position.x + borderSize, position.y + height - borderSize);
	patch2->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH3 - borderSize * 2));
	addChild(patch2);

	auto* patch4 = Sprite::create("RoomBackground.png", Rect(0, borderSize, borderSize, PATCH_HEIGHT3 - borderSize * 2));
	patch4->setAnchorPoint(Vec2(0, 0));
	patch4->setPosition(position.x, position.y + borderSize);
	patch4->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT3 - borderSize * 2));
	addChild(patch4);

	auto* patch6 = Sprite::create("RoomBackground.png", Rect(PATCH_HEIGHT3 - borderSize, borderSize, borderSize, PATCH_HEIGHT3 - borderSize * 2));
	patch6->setAnchorPoint(Vec2(0, 0));
	patch6->setPosition(position.x + width - borderSize, position.y + borderSize);
	patch6->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT3 - borderSize * 2));
	addChild(patch6);

	auto* patch8 = Sprite::create("RoomBackground.png", Rect(borderSize, PATCH_HEIGHT3 - borderSize, PATCH_WIDTH3 - borderSize * 2, borderSize));
	patch8->setAnchorPoint(Vec2(0, 0));
	patch8->setPosition(position.x + borderSize, position.y);
	patch8->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH3 - borderSize * 2));
	addChild(patch8);

	auto* patch5 = Sprite::create("RoomBackground.png", Rect(borderSize, borderSize, PATCH_WIDTH3 - borderSize * 2, PATCH_HEIGHT3 - borderSize * 2));
	patch5->setAnchorPoint(Vec2(0, 0));
	patch5->setPosition(position.x + borderSize, position.y + borderSize);
	patch5->setScale((float)(width - borderSize * 2) / (PATCH_WIDTH3 - borderSize * 2), (float)(height - borderSize * 2) / (PATCH_HEIGHT3 - borderSize * 2));
	addChild(patch5);
}


