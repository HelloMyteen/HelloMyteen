#include "ScoreBroad.h"
ScoreBroad* ScoreBroad::createScoreBroad(int score, int width, int height, const char *title,int type, float x,float y)
{	// 此处套用模板
	ScoreBroad* enemy = new ScoreBroad();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(score, width, height, title, type, x, y);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}
bool ScoreBroad::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void ScoreBroad::enemyInit(int score, int width, int height, const char *title,int type, float x, float y)
{
	this->type = type;
	this->score = score;
	if (type == 1)
	{
		this->score = score;
		background = LayerColor::create(Color4B(200, 50, 200, 0), width, height);
		background->setPosition(x, y);
		addChild(background);
		auto* label = Label::create(title, "fonts/cute.ttf", 15);
		label->setPosition(width / 2, height - 20);
		label->setTextColor(Color4B(255, 255, 0, 255));
		background->addChild(label);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(), "fonts/cute.ttf", 15);//fonts/cute.ttf
		scoreLabel->setPosition(width / 2, 30);
		scoreLabel->setTextColor(Color4B(255, 255, 0, 255));
		background->addChild(scoreLabel);
	}
	else
	{
		this->score = score;
		background = LayerColor::create(Color4B(200, 50, 200, 0), width, height);
		background->setPosition(x, y);
		addChild(background);
		auto* label = Label::create(title, "fonts/cute.ttf", 15);
		label->setPosition(width / 2, height - 20);
		label->setTextColor(Color4B(0, 0, 255, 255));
		background->addChild(label);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(), "fonts/cute.ttf", 15);
		scoreLabel->setPosition(width / 2, 30);
		scoreLabel->setTextColor(Color4B(0, 0, 255, 255));
		background->addChild(scoreLabel);
	}
}
void ScoreBroad::setScore(int number)		// 修改记分牌的分数
{
	this->score = number;
	scoreLabel->setString(String::createWithFormat("%d", number)->getCString());
}
int ScoreBroad::getScore()				// 获取记分牌显示的数字
{
	return this->score;
}
