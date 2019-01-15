#ifndef __ENDING_SCENE_H__
#define __ENDING_SCENE_H__

#include "cocos2d.h"

class EndingScene : public cocos2d::Scene //ÇÁ·Ñ·Î±× ÄÆ¾À
{
private:
	int sceneNum;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void setImage();

	void nextClicked(cocos2d::Ref* pSender);
	void previousClicked(cocos2d::Ref* pSender);
	void skipClicked(cocos2d::Ref* pSender);
	CREATE_FUNC(EndingScene);
};

#endif //__ENDING_SCENE_H__