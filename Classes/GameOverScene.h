#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene //ÇÁ·Ñ·Î±× ÄÆ¾À
{
private:
	int sceneNum;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void endAnimation(Node *node);

	void restartClicked(cocos2d::Ref* pSender);
	void mainClicked(cocos2d::Ref* pSender);
	void skipClicked(cocos2d::Ref* pSender);
	CREATE_FUNC(GameOverScene);
};

#endif //__GAMEOVER_SCENE_H__