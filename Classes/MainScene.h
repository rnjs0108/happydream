#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void setStartPane();
	void setSettingPane();
	void createToastLayer();
	void setMainButtonEnable(bool b);

	void startClicked(cocos2d::Ref* pSender);
	void newStartClicked(cocos2d::Ref* pSender);
	void continueStartClicked(cocos2d::Ref* pSender);
	void settingClicked(cocos2d::Ref* pSender);
	void BGMClicked(cocos2d::Ref* pSender);
	void EffectClicked(cocos2d::Ref* pSender);
	void okClicked(cocos2d::Ref* pSender);
	void quitClicked(cocos2d::Ref* pSender);
	CREATE_FUNC(MainScene);
};

#endif //__MAIN_SCENE_H__
