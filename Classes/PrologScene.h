#ifndef __PROLOG_SCENE_H__
#define __PROLOG_SCENE_H__

#include "cocos2d.h"

class PrologScene : public cocos2d::Scene //ÇÁ·Ñ·Î±× ÄÆ¾À
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
	CREATE_FUNC(PrologScene);
};

#endif //__PROLOG_SCENE_H__