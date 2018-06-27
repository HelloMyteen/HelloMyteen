
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
	int getType();
//	cocos2d::Vec2 getVec();
	std::string getName();
	int getHealth();			//��ȡ��λ����ֵ
	int getMaxHealth();
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
	void setType(int t);
//	void setVec(cocos2d::Vec2 pos);
	void setHealth(int h);
	void setMaxHealth(int mh);
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
	int health;						//��λ������ֵ
	int max_health;					//��λ���������ֵ
	int attack;						//��λ�Ĺ�����
	int attack_speed;				//��λ�Ĺ����ٶ�
	int defend;						//��λ�ķ�����
	float build_time;				//��λ�Ľ���ʱ��
	int price;						//��λ�ļ۸�
	bool isUnitDead = false;		//��λ�Ƿ�����
	bool isMove = true;            //��λ�Ƿ���ƶ�
};

