#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static int MAX_TUTORIAL;
private:
	Size visibleSize;
	Vec2 origin;
	bool canClick;
	int itemTypeList[4];
	int itemAniNum;
	int tutorialCase;
	int cancelNum;

	std::ostringstream textString;

	Vector<CCSpriteFrame*> playerRightStandF;
	Vector<CCSpriteFrame*> playerLeftStandF;
	Vector<CCSpriteFrame*> playerRightRunF;
	Vector<CCSpriteFrame*> playerLeftRunF;
	
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void SceneLoad();
	void PlayerStand();
	void PlayerRun();
	void ScreenFadeIn(float f);
	void ScreenFadeOut(float f);
	void GoLeftDoor();
	void GoRightDoor();
	void GoDownFloor();
	void GoNextScreen(float f);
	void setCanClick(float f) { canClick = true; };
	void setText();
	void setGageScale();
	void setMonsterImg();
	void itemGetAnimation(CCNode *node);
	void getItems();

	void addMenuLayer();
	void deleteMenuLayer();
	void setButtonEnable(bool b);
	
	void createCommuPane();
	void setCommuPane();
	void deleteCommuPane();

	void createSelectPane(int n);
	void tutorialSetting(CCNode *node);


	//게임화면 버튼동작
	void BattleClicked(cocos2d::Ref* pSender);
	void ItemClicked(cocos2d::Ref* pSender);
	void LeftClicked(cocos2d::Ref* pSender);
	void RightClicked(cocos2d::Ref* pSender);
	void NextClicked(cocos2d::Ref* pSender);
	void PharmingClicked(cocos2d::Ref* pSender);
	void EventClicked(cocos2d::Ref* pSender);
	void MenuClicked(cocos2d::Ref* pSender);
	//메뉴화면 버튼동작
	void BackClicked(cocos2d::Ref* pSender);
	void BGMClicked(cocos2d::Ref* pSender);
	void EffectClicked(cocos2d::Ref* pSender);
	void HomeClicked(cocos2d::Ref* pSender);
	//대화화면 버튼동작
	void NextTextClicked(cocos2d::Ref* pSender);
	void PreviousTextClicked(cocos2d::Ref* pSender);
	void SkipClicked(cocos2d::Ref* pSender);
	void okClicked(cocos2d::Ref* pSender);
	void cancelClicked(cocos2d::Ref* pSender);
	
	CREATE_FUNC(GameScene);
};

#endif //__GAME_SCENE_H__
