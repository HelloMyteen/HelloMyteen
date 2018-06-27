
#pragma once


#include <cocos2d.h>
#include <string>


class GameUnit :public cocos2d::Sprite {
public:
	GameUnit() = default;

	//��λ��create����
	static GameUnit* create(const std::string& filename);
	static GameUnit* createWithSpriteFrameName(const std::string & 	filename);

	//��ȡ��Ϸ��λ�������Եĺ���
	Sprite * getblood();
	Sprite * getbar();

	int getType();
//	cocos2d::Vec2 getVec();
	std::string getName();
	float getHealth();			//��ȡ��λ����ֵ
	float getMaxHealth();
	int getAttack();
	int getAttackSpeed();
	int getDefend();
	float getBuildTime();
	int getPrice();
	bool getDeathMes();

//	cocos2d::Sprite* getEffectRange();
	float getEffectRange();

	bool getIsMove();



	//�޸ĸ�������
	void setblood(Sprite * _blood);
	void setbar(Sprite * _bar);

	void setType(int t);
//	void setVec(cocos2d::Vec2 pos);
	void setHealth(float h);
	void setMaxHealth(float mh);
	void setAttack(int att);
	void setAttackSpeed(int att_spe);
	void setDefend(int def);
	void setBuildTime(float bul_tim);
	void setPrice(int pri);
	void setUnitDead();

//	void setEffectRange(cocos2d::Sprite* range);
	void setEffectRange(float range);
	void setIsMove(bool is);

private:
//	cocos2d::Sprite* effect_range;	//��λ�����÷�Χ
	float effect_range;


	int type=0;						//��λ������
//	cocos2d::Vec2 position;			//��λ��λ��
	std::string unit_name;			//��λ��id
	float health;						//��λ������ֵ
	float max_health;					//��λ���������ֵ
	int attack;						//��λ�Ĺ�����
	int attack_speed;				//��λ�Ĺ����ٶ�
	int defend;						//��λ�ķ�����
	float build_time;				//��λ�Ľ���ʱ��
	int price;						//��λ�ļ۸�
	bool isUnitDead = false;		//��λ�Ƿ�����
	bool isMove = true;            //��λ�Ƿ���ƶ�
	cocos2d::Sprite*blood;
	cocos2d::Sprite*bar;
};

