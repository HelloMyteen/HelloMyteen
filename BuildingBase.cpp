#include "BuildingBase.h"
#include "order.h"

class BuildingBase;

extern Message message;

BuildingBase* BuildingBase::create(const std::string & filename)
{
	BuildingBase *base = new BuildingBase();
	if (base&&base->initWithFile(filename))
	{
		base->autorelease();
		cocos2d::Vec2 born_position(50, 50);            //待确定
		base->setPosition(born_position);
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}

BuildingBase* BuildingBase::createWithSpriteFrameName(const std::string & filename)
{
	BuildingBase *base = new BuildingBase();
	if (base&&base->initWithSpriteFrameName(filename))
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}

void BuildingBase::isattacked_(Moveable* target)
{
	this->setHealth(this->getHealth() - target->getAttack() - this->getDefend());
	this->getblood()->setScaleX(this->getHealth() / this->getMaxHealth());
	if (getHealth() <= 0)
	{
		EraseBase();
		cocos2d::log("the unit is destroyed!");
	}
	auto fire_animation = cocos2d::Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		cocos2d::log("nullptr!!!");
		cocos2d::__String * frameName = cocos2d::__String::createWithFormat("soldierfireright%d.png", i);
		//cocos2d::SpriteFrame * spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		fire_animation->addSpriteFrameWithFile(frameName->getCString());
	}
	fire_animation->setDelayPerUnit(0.15f);
	fire_animation->setRestoreOriginalFrame(true);
	fire_animation->setLoops(1);
	auto action = cocos2d::Animate::create(fire_animation);
	message.getTargetOne()->runAction(action);
}

void BuildingBase::EraseBase()
{
	auto boom_animation = cocos2d::Animation::create();
	for (int i = 1; i <= 4; ++i)
	{

		cocos2d::__String * frameName = cocos2d::__String::createWithFormat("boom%d.png", i);
		cocos2d::log("framename %s ", frameName->getCString());
		//cocos2d::SpriteFrame * spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		boom_animation->addSpriteFrameWithFile(frameName->getCString());
	}
	boom_animation->setDelayPerUnit(0.15f);
	boom_animation->setRestoreOriginalFrame(true);
	boom_animation->setLoops(1);
	auto action = cocos2d::Animate::create(boom_animation);
	this->runAction(action);

	auto callFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(BuildingBase::boomlisten, this));
	auto sequence = cocos2d::Sequence::create(action, callFunc, NULL);
	this->runAction(sequence);
}

void BuildingBase::boomlisten()
{
	this->stopAllActions();
	this->setType(0);
	this->setIsMove(true);
	this->setPosition(-1000, -1000);

}

//待修改
void BuildingBase::initBase(int type)
{	  
	//注册监听器
	cocos2d::EventDispatcher * _eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	baselistener = cocos2d::EventListenerTouchOneByOne::create();
	baselistener->setSwallowTouches(true);
	baselistener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标

		cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		cocos2d::Size s = target->getContentSize();
		cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			if (message.getTargetOne() == nullptr)//target1无目标
			{
				cocos2d::log("it's useless");
			}
			else
			{
				std::string mes_sag;
				int attack = message.getTargetOne()->getTag();
				int isattack = this->getTag();
				std::string name = message._players[0].name;
				mes_sag = name + "&" + std::to_string(attack) + "," + std::to_string(isattack) + "%";
				if (message._players[0].flag == 1)
				{
					message._server->sendMessage(mes_sag.c_str(), mes_sag.length());
				}
				else
				{
					message._client->sendMessage(mes_sag.c_str(), mes_sag.length());
				}
				isattacked_(message.getTargetOne());
				cocos2d::log("WARNING!!! I WAS ATTACKED!!!");
				cocos2d::log("The car's blood %d", this->getHealth());
				cocos2d::log("the order is clean");
				message.clean();
			}
			return true;
		}
		else
		{
			return false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(baselistener, this);

	this->setType(type);
	if (type == BUIDBASE_TYPE)
	{
		setHealth(BUIDBASE_HEALTH);
		setMaxHealth(BUIDBASE_MAXHEALTH);
		setDefend(BUIDBASE_DEFEND);
		setIsMove(false);
		auto frame = cocos2d::SpriteFrame::create("base.png", cocos2d::Rect(0, 0, 99, 99));
		this->setDisplayFrame(frame);
	}
}
