#include "PrologScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "GameScene.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

Scene* PrologScene::createScene()
{
	return PrologScene::create();
}

// on "init" you need to initialize your instance
bool PrologScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	sceneNum = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//텍스트 데이터 불러오기
	GameData::getTextManager()->createText("prologText.txt");

	auto BGImage = CCSprite::create("gfx/cutScene/prolog00.png");
	BGImage->setName("BGImage");
	BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 150));

	auto nextButton = MenuItemImage::create(
		"gfx/icon/nextText.png",
		"gfx/icon/nextText_clicked.png",
		CC_CALLBACK_1(PrologScene::nextClicked, this));
	nextButton->setName("nextButton");
	nextButton->setPosition(Point(420, 60));
	auto previousButton = MenuItemImage::create(
		"gfx/icon/previousText.png",
		"gfx/icon/previousText_clicked.png",
		CC_CALLBACK_1(PrologScene::previousClicked, this));
	previousButton->setName("previousButton");
	previousButton->setPosition(Point(60, 60));
	previousButton->setVisible(false);
	previousButton->setEnabled(false);
	auto skipButton = MenuItemImage::create(
		"gfx/icon/skip_icon.png",
		"gfx/icon/skip_icon_clicked.png",
		CC_CALLBACK_1(PrologScene::skipClicked, this));
	skipButton->setName("skipButton");
	skipButton->setPosition(Point(400, 740));
	
	auto pMenu = Menu::create(nextButton, previousButton, skipButton, NULL);
	pMenu->setName("pMenu");
	pMenu->setPosition(Point::ZERO);

	addChild(BGImage, 0);
	addChild(pMenu, 2);

	setImage();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/prologBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	return true;
}

void PrologScene::setImage()
{
	auto BGImage = getChildByName<CCSprite*>("BGImage");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	CCSprite* newImage;
	getActionManager()->removeAllActions();
	if (sceneNum == 0) {
		removeChild(BGImage);
		newImage = CCSprite::create("gfx/cutScene/prolog00.png");
		newImage->setName("BGImage");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 200));
		addChild(newImage, 0);
		newImage->runAction(MoveBy::create(8.0f, Vec2(0, 400)));
	}
	else if (sceneNum == 1) {
		removeChild(BGImage);
		newImage = CCSprite::create("gfx/cutScene/prolog01.png");
		newImage->setName("BGImage");
		newImage->setPosition(Point(120, visibleSize.height / 2));
		addChild(newImage, 0);
		newImage->runAction(MoveBy::create(4.0f, Vec2(280, 0)));
	}
	else if (sceneNum == 2) {
		removeChild(BGImage);
		auto layer = Layer::create();
		layer->setName("BGImage");
		layer->setPosition(Point::ZERO);
		newImage = CCSprite::create("gfx/cutScene/prolog02.png");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto dedImage = CCSprite::create("gfx/cutScene/prolog02_m.png");
		dedImage->setPosition(Point(visibleSize.width / 2 + 50, visibleSize.height / 2 + 10));
		auto backImage = CCSprite::create("gfx/cutScene/prolog02_b.png");
		backImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		layer->addChild(newImage, 0);
		layer->addChild(dedImage, 1);
		layer->addChild(backImage, 2);
		addChild(layer, 0);
		dedImage->runAction(Sequence::create(
			MoveBy::create(0.5f, Vec2(-50, -10)),
			DelayTime::create(1.0f),
			MoveBy::create(0.5f, Vec2(30, 5)),
			nullptr
		));
	}
	else if (sceneNum == 3) {
		removeChild(BGImage);
		newImage = CCSprite::create("gfx/cutScene/prolog03.png");
		newImage->setName("BGImage");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		addChild(newImage, 0);
	}
	else if (sceneNum == 4) {
		BGImage->stopAllActions();
		BGImage->setTexture(CCSprite::create("gfx/cutScene/prolog04.png")->getTexture());
		BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		BGImage->setScale(1.0f);
	}
	else if (sceneNum == 5) {
		BGImage->setTexture(CCSprite::create("gfx/cutScene/prolog05.png")->getTexture());
		BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		BGImage->runAction(Spawn::create(
			MoveBy::create(4.0f, Vec2(100, 20)),
			ScaleBy::create(4.0f, 1.5f),
			nullptr
		));
	}
	else if (sceneNum == 6) {
		removeChild(BGImage);
		newImage = CCSprite::create("gfx/cutScene/prolog06.png");
		newImage->setName("BGImage");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		addChild(newImage, 0);
	}
	else if (sceneNum == 7) {
		removeChild(BGImage);
		auto layer = Layer::create();
		layer->setName("BGImage");
		layer->setPosition(Point::ZERO);
		newImage = CCSprite::create("gfx/cutScene/prolog07.png");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto darkImage = CCSprite::create("gfx/backGround/blackScreen.png");
		darkImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		layer->addChild(newImage, 0);
		layer->addChild(darkImage, 1);
		addChild(layer, 0);
		darkImage->runAction(Sequence::create(
			DelayTime::create(0.5f),
			FadeTo::create(0.5f, 20),
			nullptr
		));
	}
	else if (sceneNum == 8) {
		removeChild(BGImage);
		auto layer = Layer::create();
		layer->setName("BGImage");
		layer->setPosition(Point::ZERO);
		newImage = CCSprite::create("gfx/cutScene/prolog08.png");
		newImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto darkImage = CCSprite::create("gfx/backGround/blackScreen.png");
		darkImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		layer->addChild(newImage, 0);
		layer->addChild(darkImage, 1);
		addChild(layer, 0);
		darkImage->runAction(Sequence::create(
			DelayTime::create(0.2f),
			FadeTo::create(0.5f, 20),
			nullptr
		));
	}
}

void PrologScene::nextClicked(cocos2d::Ref * pSender)
{
	log("next clicked!");
	if (sceneNum == 8) {
		//게임화면 돌입
		GameData::getInGameData()->setNewGameSetting(0);
		auto gameScene = CCTransitionFade::create(1.0f, GameScene::createScene());
		Director::getInstance()->replaceScene(gameScene);
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
		if (GameData::getGameData()->getBGM() == 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}
	else {
		sceneNum++;
		if (sceneNum > 0) {
			auto previousButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("previousButton");
			previousButton->setVisible(true);
			previousButton->setEnabled(true);
		}
		setImage();
	}
}

void PrologScene::previousClicked(cocos2d::Ref * pSender)
{
	log("previous clicked!");
	sceneNum--;
	if (sceneNum == 0) {
		auto previousButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("previousButton");
		previousButton->setVisible(false);
		previousButton->setEnabled(false);
	}
	setImage();
}

void PrologScene::skipClicked(cocos2d::Ref * pSender)
{
	log("skip clicked!");
	GameData::getInGameData()->setNewGameSetting(0);
	auto gameScene = CCTransitionFade::create(1.0f, GameScene::createScene());
	Director::getInstance()->replaceScene(gameScene);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}
