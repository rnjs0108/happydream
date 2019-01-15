#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BattleScene : public cocos2d::LayerColor
{
public:
	static int MAX_TUTORIAL;
private:
	int situNum; //0=기본, 1=전투, 2=대화, 3=선물, 4=종료
	int textNum;
	int type;
	std::ostringstream textString;
	int tutorialCase;
	int cancelNum;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void setBattleText();
	void setMonsterImg();
	void setDeadMonsterImg(CCNode *node);
	void setText();
	void setGageScale();
	void setGageText();
	void setSettings();

	bool isBattleEnd();
	void commuStart();
	void commuEnd();
	void setActText();
	void setActNumber();
	void runAwayFromMonster();
	void setButtonEnable(bool b);

	void createTextPane();
	void setTextPane();
	void fadeOutTextPane(CCNode *node);
	void removeTextPane(CCNode *node);

	void createCommuPane();
	void setCommuPane();
	void deleteCommuPane();

	void tutorialSetting(CCNode *node);

	void monsterBreathAnimation();
	void monsterVoidAnimation();
	void monsterDamagedAnimation();
	void monsterAttackAnimation();
	void monsterComuAnimation1();
	void monsterComuAnimation2();
	void monsterComuAnimation3();
	void monsterDeadAnimation();
	void monsterHappyAnimation();
	void playerDamagedEffect();

	std::string battle_attack(int t);
	std::string battle_week(int t);
	std::string battle_damaged(int t);
	int sumDamage(int type, int at, int de);

	void button1Clicked(cocos2d::Ref* pSender);
	void button2Clicked(cocos2d::Ref* pSender);
	void button3Clicked(cocos2d::Ref* pSender);
	void button4Clicked(cocos2d::Ref* pSender);
	void backButtonClicked(cocos2d::Ref* pSender);
	void nextButtonClicked(cocos2d::Ref* pSender);

	void NextTextClicked(cocos2d::Ref* pSender);
	void PreviousTextClicked(cocos2d::Ref* pSender);
	void SkipClicked(cocos2d::Ref* pSender);

	CREATE_FUNC(BattleScene);
};

#endif //__BATTLE_SCENE_H_