#ifndef __EVENT_SCENE_H__
#define __EVENT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class EventScene : public cocos2d::LayerColor
{
private:
	Size visibleSize;
	Vec2 origin;
	Vector<CCSpriteFrame*> playerRightStandF;
	Vector<CCSpriteFrame*> playerLeftStandF;
	int choiceNum;
	int caseNum;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void PlayerStand();
	CCSprite* setStatueImage();
	int setSituation();

	void createCommuPane();
	void setCommuPane();
	void deleteCommuPane();

	void createChoicePane(); //선택판
	void setChoicePane(CCNode *node);

	void runEvent(); //이벤트 실행

	void NextTextClicked(cocos2d::Ref* pSender);
	void PreviousTextClicked(cocos2d::Ref* pSender);
	void SkipClicked(cocos2d::Ref* pSender);
	void okClicked(cocos2d::Ref* pSender);
	void cancelClicked(cocos2d::Ref* pSender);

	CREATE_FUNC(EventScene);
};

#endif //__EVENT_SCENE_H_