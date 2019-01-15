#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "MainScene.h"
#include "PrologScene.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	DatabaseManager::getInstance()->deleteAllData();
	DatabaseManager::getInstance()->saveSettingData();
	sceneNum = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	std::ostringstream textString;
	textString.str("");
	textString.clear();

	//텍스트 데이터 불러오기
	GameData::getTextManager()->createText("GameOverText.txt");

	auto BGImage = CCSprite::create("gfx/backGround/blackScreen.png");
	BGImage->setName("BGImage");
	BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto textLayer = Layer::create();
	textLayer->setName("textLayer");
	textLayer->setPosition(Point::ZERO);
	auto GameOverLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/MarkerFelt.ttf", 74, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	GameOverLabel->setName("GameOverLabel");
	GameOverLabel->setPosition(Point(visibleSize.width / 2, 920));
	GameOverLabel->setColor(Color3B::WHITE);
	auto floorLabel = Label::createWithTTF("", "fonts/THE_Oegyeinseolmyeongseo.ttf", 48, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	floorLabel->setName("floorLabel");
	floorLabel->setPosition(Point(540, 550));
	floorLabel->setColor(Color3B::WHITE);
	textString << GameData::getInGameData()->getFloorNum();
	textString << GameData::getTextManager()->getTextList()->pop();
	floorLabel->setString(textString.str());
	textString.str("");
	textString.clear();
	auto monsterLabel = Label::createWithTTF("", "fonts/THE_Oegyeinseolmyeongseo.ttf", 48, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	monsterLabel->setName("monsterLabel");
	monsterLabel->setPosition(Point(540, 450));
	monsterLabel->setColor(Color3B::WHITE);
	textString << GameData::getInGameData()->getMonsterKill();
	textString << GameData::getTextManager()->getTextList()->pop();
	monsterLabel->setString(textString.str());
	textString.str("");
	textString.clear();
	auto restartButton = MenuItemImage::create(
		"gfx/icon/selectButton.png",
		"gfx/icon/selectButton_clicked.png",
		CC_CALLBACK_1(GameOverScene::restartClicked, this));
	restartButton->setName("restartButton");
	restartButton->setPosition(Point(120, -120));
	restartButton->setEnabled(false);
	auto restartLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/NanumPen.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	restartLabel->setPosition(Point(60, 40));
	restartLabel->setColor(Color3B::BLACK);
	restartButton->setScale(1.5f);
	restartButton->addChild(restartLabel);
	auto mainButton = MenuItemImage::create(
		"gfx/icon/selectButton.png",
		"gfx/icon/selectButton_clicked.png",
		CC_CALLBACK_1(GameOverScene::mainClicked, this));
	mainButton->setName("mainButton");
	mainButton->setPosition(Point(360, -120));
	mainButton->setEnabled(false);
	auto mainLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/NanumPen.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	mainLabel->setPosition(Point(60, 40));
	mainLabel->setColor(Color3B::BLACK);
	mainButton->setScale(1.5f);
	mainButton->addChild(mainLabel);

	auto skipButton = MenuItemImage::create(
		"gfx/icon/skip_icon.png",
		"gfx/icon/skip_icon_clicked.png",
		CC_CALLBACK_1(GameOverScene::skipClicked, this));
	skipButton->setName("skipButton");
	skipButton->setPosition(Point(400, 740));

	auto pMenu = Menu::create(restartButton, mainButton, skipButton, NULL);
	pMenu->setName("pMenu");
	pMenu->setPosition(Point::ZERO);

	textLayer->addChild(GameOverLabel);
	textLayer->addChild(floorLabel);
	textLayer->addChild(monsterLabel);

	addChild(BGImage, 0);
	addChild(textLayer, 1);
	addChild(pMenu, 2);

	GameOverLabel->runAction(Sequence::create(
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(visibleSize.width / 2, 680)),
		nullptr
	));
	floorLabel->runAction(Sequence::create(
		DelayTime::create(2.5f),
		MoveTo::create(0.5f, Vec2(340, 550)),
		nullptr
	));
	monsterLabel->runAction(Sequence::create(
		DelayTime::create(3.5f),
		MoveTo::create(0.5f, Vec2(340, 450)),
		nullptr
	));
	restartButton->runAction(Sequence::create(
		DelayTime::create(4.5f),
		MoveTo::create(0.3f, Vec2(120, 160)),
		nullptr
	));
	mainButton->runAction(Sequence::create(
		DelayTime::create(5.0f),
		MoveTo::create(0.3f, Vec2(360, 160)),
		nullptr
	));

	CCDelayTime * delayAction = CCDelayTime::create(5.3f);
	CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(GameOverScene::endAnimation));
	this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/overBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	return true;
}

void GameOverScene::endAnimation(Node * node)
{
	auto GameOverLabel = getChildByName("textLayer")->getChildByName<Label*>("GameOverLabel");
	auto floorLabel = getChildByName("textLayer")->getChildByName<Label*>("floorLabel");
	auto monsterLabel = getChildByName("textLayer")->getChildByName<Label*>("monsterLabel");
	auto skipButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("skipButton");
	auto restartButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("restartButton");
	auto mainButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("mainButton");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	getActionManager()->removeAllActions();
	GameOverLabel->stopAllActions();
	floorLabel->stopAllActions();
	monsterLabel->stopAllActions();
	skipButton->stopAllActions();
	restartButton->stopAllActions();
	mainButton->stopAllActions();

	GameOverLabel->setPosition(Point(visibleSize.width / 2, 680));
	floorLabel->setPosition(Point(340, 550));
	monsterLabel->setPosition(Point(340, 450));
	restartButton->setPosition(Point(120, 160));
	mainButton->setPosition(Point(360, 160));
	skipButton->setEnabled(false);
	skipButton->setVisible(false);
	restartButton->setEnabled(true);
	mainButton->setEnabled(true);
	restartButton->setOpacity(255);
	mainButton->setOpacity(255);
}

void GameOverScene::restartClicked(cocos2d::Ref * pSender)
{
	log("next clicked!");
	GameData::getInGameData()->setNewGameSetting(0);
	auto gameScene = CCTransitionFade::create(1.0f, PrologScene::createScene());
	Director::getInstance()->replaceScene(gameScene);
}

void GameOverScene::mainClicked(cocos2d::Ref * pSender)
{
	log("previous clicked!");
	auto mainScene = CCTransitionFade::create(1.2f, MainScene::createScene());
	Director::getInstance()->replaceScene(mainScene);
}

void GameOverScene::skipClicked(cocos2d::Ref * pSender)
{
	log("skip clicked!");
	endAnimation(NULL);
}
