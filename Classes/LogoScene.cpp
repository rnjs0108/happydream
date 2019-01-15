#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "MainScene.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

Scene* LogoScene::createScene()
{
	return LogoScene::create();
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto BGImage = CCSprite::create("gfx/backGround/logo.png");
	BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto whiteScreen = CCSprite::create("gfx/backGround/whiteScreen.png");
	whiteScreen->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	addChild(BGImage, 0);
	addChild(whiteScreen, 1);
	
	whiteScreen->runAction(Sequence::create(
		FadeOut::create(1.0f),
		DelayTime::create(1.0f),
		FadeIn::create(1.0f),
		nullptr
	));
	CCDelayTime * delayAction = CCDelayTime::create(3.0f);
	CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(LogoScene::goMainScene));
	this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));
	//log("whiteScreen Path : %s", whiteScreen->getResourceName());

	return true;
}

void LogoScene::goMainScene(CCNode * node)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
