//
//  Moveable.cpp
//  experiment-mobile
//
//  Created by 叶琪 on 2018/6/23.
//

#include "order.h"
#include "Moveable.h"
#include "Toast.h"


class Moveable;

extern Message message;

void Moveable::updateBloodBar(int Health, int MaxHealth, cocos2d::Sprite* _blood)
{
    float ValueScale = Health / MaxHealth;
    _blood->setScaleX(ValueScale);
}


Moveable* Moveable::create(const std::string& filename)
{
    Moveable* moveable = new Moveable();
    if (moveable&&moveable->initWithFile(filename))
    {
        moveable->autorelease();
        //    moveable->setEffectRange(cocos2d::Sprite::create("∑∂Œß"));
        cocos2d::Vec2 born_position(-1000, -1000);
        moveable->setPosition(born_position);
        //    moveable->getEffectRange.setPosition(born_position);
        return moveable;
    }
    CC_SAFE_DELETE(moveable);
    return nullptr;
}

Moveable* Moveable::createWithSpriteFrameName(const std::string & filename)
{

    Moveable* moveable = new Moveable();
    if (moveable&&moveable->initWithSpriteFrameName(filename))
    {
        moveable->autorelease();
        return moveable;
    }
    CC_SAFE_DELETE(moveable);
    return nullptr;
}

void Moveable::eraseMoveable()
{
    this->stopAllActions();

    /*◊¢œ˙º‡Ã˝∆˜*/
    this->setType(0);
    this->setPosition(-1000, -1000);
}

void Moveable::moveMoveable(cocos2d::Vec2 destination)
{
    this->stopAllActions();
    float distance = this->getPosition().distance(destination);
    float movetime = distance / getMoveSpeed() / 33 / 2;
    auto * moveMoveableaction = cocos2d::MoveTo::create(movetime, destination);

    if (this->getPosition().x - destination.x > 0)
        //œÚ◊Û
    {
		changeDirect(false);
    }
    else
    {
        changeDirect(true);
    }

    auto move_animation = cocos2d::Animation::create();
    for (int i = 1; i <= 4; ++i)
    {

        std::string str = this->getTypeName()+this->getDirection()+"move";
        auto frameName = cocos2d::__String::createWithFormat("%s%d.png",str.c_str(), i);

//        auto frameName = cocos2d::__String::createWithFormat("soldier%smove%d.png", direct.c_str(), i);
        move_animation->addSpriteFrameWithFile(frameName->getCString());

    }
    move_animation->setDelayPerUnit(0.15f);
    move_animation->setRestoreOriginalFrame(true);
    move_animation->setLoops(-1);
    auto move_action = cocos2d::Animate::create(move_animation);

    auto ac1 = (cocos2d::FiniteTimeAction*)(this)->runAction(moveMoveableaction);
    auto ac2 = (cocos2d::FiniteTimeAction*)(this)->runAction(move_action);
    this->runAction(cocos2d::Spawn::create(ac1, ac2, NULL));

    //当以上动作完成时执行下边的
    auto callFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(Moveable::movelisten, this));
    auto sequence = cocos2d::Sequence::create(moveMoveableaction,callFunc,NULL);
    this->runAction(sequence);
}

bool Moveable::canattack(Moveable* target)
{
    /* 是否在擦枪时间内 */
    if (!target->getAttackable())
    {
		auto toast = Toast::create("正在擦枪！！无法攻击", 25, 1);
		addChild(toast);
        
        return false;
    }
    float distance = this->getPosition().distance(target->getPosition());
    if (distance > this->getEffectRange())
    {
		auto toast = Toast::create("too far away!!", 25, 1);
		addChild(toast);
        return false;
    }
    
    return true;
    
}

void Moveable::isattacked(Moveable* target)
{
    this->setHealth(this->getHealth() - target->getAttack() - this->getDefend());
	this->getblood()->setScaleX(this->getHealth() / this->getMaxHealth());
    if (getHealth() <= 0)
    {
        eraseMoveable();
        cocos2d::log("the unit is destroyed!");
    }
 
    if(target->getPosition().x-this->getPosition().x>0)
    //应该向左方开火，加入方向为真，那么应该转方向
    {
        if(target->getDirect())
        {
            target->changeDirect(false);
            std::string str = target->getTypeName() + target->getDirection() + ".png";
            auto frame = cocos2d::SpriteFrame::create(str, cocos2d::Rect(0, 0, 99, 99));
            target->setDisplayFrame(frame);
        }
    }
    else
    {
        if(!target->getDirect())
        {
            target->changeDirect(true);
            std::string str = target->getTypeName() + target->getDirection() + ".png";
            auto frame = cocos2d::SpriteFrame::create(str, cocos2d::Rect(0, 0, 99, 99));
            target->setDisplayFrame(frame);
        }
    }

    /*π•ª˜ƒø±Í÷¥––ø™ªÃÿ–ß ±ªπ•ª˜ƒø±Í÷¥–– ‹…ÀÃÿ–ß */
    
    auto fire_animation = cocos2d::Animation::create();
    for (int i = 1; i <= 4; ++i)
    {
//        cocos2d::log("nullptr!!!");
//        std::string str=target->getTypeName()+"fire"+target->getDirection()+".png";
//        cocos2d::__String * frameName = cocos2d::__String::createWithFormat("%sfire%s%d.png", target->getTypeName().c_str,target->getDirection?().c_str(),i : );
//        cocos2d::SpriteFrame * spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
        std::string str = target->getTypeName() + "fire";
        str+=target->getDirection();
        cocos2d::log("%s",str.c_str());
        auto frameName = cocos2d::__String::createWithFormat("%s%d.png",str.c_str(), i);
        cocos2d::log("%s",frameName->getCString());
        fire_animation->addSpriteFrameWithFile(frameName->getCString());
    }
    fire_animation->setDelayPerUnit(0.15f);
    fire_animation->setRestoreOriginalFrame(true);
    fire_animation->setLoops(1);
    auto action = cocos2d::Animate::create(fire_animation);
    target->runAction(action);
}

float Moveable::getMoveSpeed()
{
    return movespeed;
}

void Moveable::setMoveSpeed(float speed)
{
    movespeed = speed;
}

bool Moveable::getAttackable()
{
    return attackable;
}

void Moveable::setAttackable(const bool b)
{
    attackable = b;
}

bool Moveable::getDirect()
{
    return direction;
}

std::string Moveable::getDirection()
{
    return direct;
}

void Moveable::changeDirect(const bool dir)
{
    direction = dir;
    if (!dir)
        //Œ™ºŸœÚ◊Û
    {
        direct = "left";
    }
    else
    {
        direct = "right";
    }
}

std::string Moveable::getTypeName()
{
    return type_name;
}

void Moveable::setTypeName(const std::string str)
{
    type_name = str;
}



void Moveable::addMoveable(const cocos2d::Vec2 pos, int type)
{
    cocos2d::EventDispatcher * eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());//ªÒ»°µƒµ±«∞¥•√˛µƒƒø±Í

        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Size s = target->getContentSize();
        cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))//≈–∂œ¥•√˛µ„ «∑Ò‘⁄ƒø±Íµƒ∑∂Œßƒ⁄
        {
            if (message.getTargetOne() == nullptr)//target1Œﬁƒø±Í
            {
                if(false)//欲操控的单位不属于玩家，直接结束该操作
                {
                    return true;
                }
                message.setTargetOne(this);
                message.setOrder("move");
                cocos2d::log("you will move if you touch map");
                cocos2d::log("you will attack sth if you touch sth");
            }
            else
            {
                if(canattack(message.getTargetOne()))//判断是否可以攻击 条件有距离，权限，以及是否在擦枪时间
                {
					std::string mes_sag;
					int attack= message.getTargetOne()->getTag();
					int isattack=this->getTag();
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
                    isattacked(message.getTargetOne());
                    cocos2d::log("WARNING!!! I WAS ATTACKED!!!");
                    cocos2d::log("The car's blood %d", this->getHealth());
                    
                    message.getTargetOne()->setAttackable(false);
					message.getTargetOne()->scheduleOnce(schedule_selector(Moveable::updateGum), 
						message.getTargetOne()->getAttackSpeed());
                    message.clean();
                    cocos2d::log("the order is clean");
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    };
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->setType(type);
    changeDirect(true);
    setAttackable(true);
    if (type == TANK_TYPE)
    {
        setTypeName("tank");
        setHealth(TANK_HEALTH);
        setMaxHealth(TANK_MAXHEALTH);
        setAttack(TANK_ATTACK);
        setAttackSpeed(TANK_ATTACK_SPEED);
        setDefend(TANK_DEFEND);
        setBuildTime(TANK_BUILD_TIME);
        setPrice(TANK_PRICE);
        setMoveSpeed(TANK_MOVESPEED);
        setEffectRange(TANK_EFFECT_RANGE);
        auto frame = cocos2d::SpriteFrame::create("che.png", cocos2d::Rect(0, 0, 99, 99));
        this->setDisplayFrame(frame);

        cocos2d::log("confirm build car");
    }
    else if (type == SOLDIER_TYPE)
    {
        setTypeName("soldier");
        setHealth(SOLDIER_HEALTH);
        setMaxHealth(SOLDIER_MAXHEALTH);
        setAttack(SOLDIER_ATTACK);
        setAttackSpeed(SOLDIER_ATTACK_SPEED);
        setDefend(SOLDIER_DEFEND);
        setBuildTime(SOLDIER_BUILD_TIME);
        setPrice(SOLDIER_PRICE);
        setMoveSpeed(SOLDIER_MOVESPEED);
        setEffectRange(SOLDIER_EFFECT_RANGE);
        auto frame = cocos2d::SpriteFrame::create("soldierright.png", cocos2d::Rect(0, 0, 99, 99));
        this->setDisplayFrame(frame);
    }
    else if (type == DOG_TYPE)
    {
        setTypeName("dog");
        setHealth(DOG_HEALTH);
        setMaxHealth(DOG_MAXHEALTH);
        setAttack(DOG_ATTACK);
        setAttackSpeed(DOG_ATTACK_SPEED);
        setDefend(DOG_DEFEND);
        setBuildTime(DOG_BUILD_TIME);
        setPrice(DOG_PRICE);
        setMoveSpeed(DOG_MOVESPEED);
        setEffectRange(DOG_EFFECT_RANGE);
        auto frame = cocos2d::SpriteFrame::create("BEAR.png", cocos2d::Rect(0, 0, 99, 99));
        this->setDisplayFrame(frame);
    }
    setPosition(pos);
    scheduleUpdate();
}

void Moveable::movelisten()
{
    stopAllActions();
    std::string str = getTypeName() + getDirection() + ".png";
    auto frame = cocos2d::SpriteFrame::create(str.c_str(), cocos2d::Rect(0, 0, 99, 99));
    this->setDisplayFrame(frame);
}

void Moveable::update(float dt)
{
	getblood()->setAnchorPoint(Vec2(0, 0.5));
	getblood()->setPosition(Vec2(getPosition().x-50,getPosition().y+50));
	getbar()->setPosition(Vec2(getPosition().x, getPosition().y + 50));
}

void Moveable::updateGum(float dt)
{
	setAttackable(true);
	cocos2d::log("可以打了");
}

void Moveable::updateBlood(float dt)
{

}
