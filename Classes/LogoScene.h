#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class LogoScene : public cocos2d::Scene //ÇÁ·Ñ·Î±× ÄÆ¾À
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void goMainScene(CCNode *node);

	CREATE_FUNC(LogoScene);
};

#endif //__LOGO_SCENE_H__