#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "GameScene.h"
#include "GameData.h"
#include "PrologScene.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

Scene* MainScene::createScene()
{
	return MainScene::create();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	DatabaseManager::getInstance()->loadSettingData();
	auto BGLayer = Layer::create();
	BGLayer->setPosition(Point::ZERO);
	auto BGImage = CCSprite::create("gfx/backGround/mainBG.png");
	BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 200));
	auto tower = CCSprite::create("gfx/backGround/mainBG_tower.png");
	tower->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 200));
	auto cloudLayer = Layer::create();
	cloudLayer->setPosition(Point(visibleSize.width, visibleSize.height / 2 + 200));
	auto cloud1 = CCSprite::create("gfx/backGround/mainBG_cloud.png");
	auto cloud2 = CCSprite::create("gfx/backGround/mainBG_cloud.png");
	cloud1->setPosition(Point(0, 400));
	cloud2->setPosition(Point(960, 400));
	cloudLayer->addChild(cloud1);
	cloudLayer->addChild(cloud2);
	BGLayer->addChild(BGImage, 0);
	BGLayer->addChild(cloudLayer, 1);
	BGLayer->addChild(tower, 2);

	auto titleImage = CCSprite::create("gfx/object/title.png");
	titleImage->setPosition(Point(visibleSize.width / 2, 960));

	auto mainContentPane = CCSprite::create("gfx/object/mainContentPane.png");
	mainContentPane->setName("mainContentPane");
	mainContentPane->setScale(1.2f);
	mainContentPane->setPosition(Point(-144, visibleSize.height / 2 - 120));
	//텍스트 불러오기
	GameData::getTextManager()->createText("mainScene2.txt");
	auto NewStartButton = MenuItemImage::create(
		"gfx/icon/MainNewStartIcon.png",
		"gfx/icon/MainNewStartIcon.png",
		CC_CALLBACK_1(MainScene::newStartClicked, this));
	NewStartButton->setName("NewStartButton");
	NewStartButton->setPosition(Point(90, 290));
	auto newStartLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/NanumPen.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	newStartLabel->setPosition(Point(90, 10));
	newStartLabel->setColor(Color3B::BLACK);
	NewStartButton->addChild(newStartLabel);
	auto ContinueStartButton = MenuItemImage::create(
		"gfx/icon/MainContinueStartIcon.png",
		"gfx/icon/MainContinueStartIcon.png",
		CC_CALLBACK_1(MainScene::continueStartClicked, this));
	ContinueStartButton->setName("ContinueStartButton");
	ContinueStartButton->setPosition(Point(90, 110));
	auto ContinueStartLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/NanumPen.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	ContinueStartLabel->setPosition(Point(90, 10));
	ContinueStartLabel->setColor(Color3B::BLACK);
	ContinueStartButton->addChild(ContinueStartLabel);
	auto startMenu = Menu::create(NewStartButton, ContinueStartButton, NULL);
	startMenu->setName("startMenu");
	startMenu->setPosition(Point::ZERO);
	mainContentPane->addChild(startMenu);
	NewStartButton->setEnabled(false);
	ContinueStartButton->setEnabled(false);

	auto mainSettingPane = CCSprite::create("gfx/object/mainSettingPane.png");
	mainSettingPane->setName("mainSettingPane");
	mainSettingPane->setScale(1.2f);
	mainSettingPane->setPosition(Point(-144, visibleSize.height / 2 - 120));
	auto BGMButton = MenuItemImage::create(
		"gfx/icon/audio_on.png",
		"gfx/icon/audio_on.png",
		CC_CALLBACK_1(MainScene::BGMClicked, this));
	BGMButton->setName("BGMButton");
	BGMButton->setPosition(Point(60, 300));
	BGMButton->setScale(0.8f);
	auto BGMLabel = Label::createWithTTF("BGM", "fonts/NanumPen.ttf", 26, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	BGMLabel->setPosition(Point(60, 230));
	BGMLabel->setColor(Color3B::BLACK);
	auto EffectButton = MenuItemImage::create(
		"gfx/icon/audio_on.png",
		"gfx/icon/audio_on.png",
		CC_CALLBACK_1(MainScene::EffectClicked, this));
	EffectButton->setName("EffectButton");
	EffectButton->setPosition(Point(60, 140));
	EffectButton->setScale(0.8f);
	auto EffectLabel = Label::createWithTTF("Effect", "fonts/NanumPen.ttf", 26, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	EffectLabel->setPosition(Point(60, 70));
	EffectLabel->setColor(Color3B::BLACK);
	auto settingMenu = Menu::create(BGMButton, EffectButton, NULL);
	settingMenu->setName("settingMenu");
	settingMenu->setPosition(Point::ZERO);
	mainSettingPane->addChild(settingMenu, 0);
	mainSettingPane->addChild(BGMLabel, 1);
	mainSettingPane->addChild(EffectLabel, 2);
	BGMButton->setEnabled(false);
	EffectButton->setEnabled(false);


	if (GameData::getGameData()->getBGM() == 0) {
		BGMButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		BGMButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
	}
	if (GameData::getGameData()->getEffect() == 0) {
		EffectButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		EffectButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
	}

	//텍스트 데이터 불러오기
	GameData::getTextManager()->createText("mainScene1.txt");
	auto StartButton = MenuItemImage::create(
		"gfx/icon/mainButton.png",
		"gfx/icon/mainButton.png",
		CC_CALLBACK_1(MainScene::startClicked, this));
	StartButton->setName("StartButton");
	StartButton->setPosition(Point(visibleSize.width + 120, 420));
	auto startLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/THE_Ppikkeutppikkeut.ttf", 34, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	startLabel->setPosition(Point(115, 50));
	startLabel->setColor(Color3B::WHITE);
	StartButton->addChild(startLabel);
	auto SettingButton = MenuItemImage::create(
		"gfx/icon/mainButton.png",
		"gfx/icon/mainButton.png",
		CC_CALLBACK_1(MainScene::settingClicked, this));
	SettingButton->setName("SettingButton");
	SettingButton->setPosition(Point(visibleSize.width + 120, 300));
	auto settingLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/THE_Ppikkeutppikkeut.ttf", 34, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	settingLabel->setPosition(Point(115, 50));
	settingLabel->setColor(Color3B::WHITE);
	SettingButton->addChild(settingLabel);
	auto QuitButton = MenuItemImage::create(
		"gfx/icon/mainButton.png",
		"gfx/icon/mainButton.png",
		CC_CALLBACK_1(MainScene::quitClicked, this));
	QuitButton->setName("QuitButton");
	QuitButton->setPosition(Point(visibleSize.width + 120, 180));
	auto quitLabel = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/THE_Ppikkeutppikkeut.ttf", 34, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	quitLabel->setPosition(Point(115, 50));
	quitLabel->setColor(Color3B::WHITE);
	QuitButton->addChild(quitLabel);
	

	auto pMenu = Menu::create(StartButton,SettingButton,QuitButton,NULL);
	pMenu->setName("pMenu");
	pMenu->setPosition(Point::ZERO);

	auto copyLabelImage = CCSprite::create("gfx/object/copyRightLabel.png");
	copyLabelImage->setPosition(Point(visibleSize.width / 2, 20));
	auto copyLabel = Label::createWithTTF("COPYRIGHTⓒ 2018. YOUNGBOT ALL RIGHTS RESERVED.", "fonts/NanumGothic.ttf", 14, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	copyLabel->setPosition(Point(240, 10));
	copyLabel->setColor(Color3B::WHITE);
	copyLabelImage->addChild(copyLabel);
	
	addChild(BGLayer, 0);
	addChild(titleImage, 1);
	addChild(mainSettingPane, 2);
	addChild(mainContentPane, 3);
	addChild(pMenu, 4);
	addChild(copyLabelImage, 5);

	StartButton->runAction(Sequence::create(
		DelayTime::create(1.0f),
		EaseOut::create(MoveBy::create(0.5f, Vec2(-220, 0)), 1.0f),
		nullptr));
	SettingButton->runAction(Sequence::create(
		DelayTime::create(1.5f),
		EaseOut::create(MoveBy::create(0.5f, Vec2(-220, 0)), 1.0f),
		nullptr));
	QuitButton->runAction(Sequence::create(
		DelayTime::create(2.0f),
		EaseOut::create(MoveBy::create(0.5f, Vec2(-220, 0)), 1.0f),
		nullptr));
	BGLayer->runAction(MoveBy::create(5.0f, Vec2(0, -400)));
	cloudLayer->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(2.0f, 1.05f),
			ScaleTo::create(2.0f, 1),
			nullptr)));
	cloudLayer->runAction(RepeatForever::create(
		Sequence::create(
			MoveBy::create(12.0f, Vec2(-960, 0)),
			MoveBy::create(0, Vec2(960, 0)),
			nullptr)));
	titleImage->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(1.5f, 1 * 1.1),
			ScaleTo::create(1.5f, 1),
			nullptr)));
	titleImage->runAction(EaseElasticInOut::create(MoveTo::create(2.0f, Vec2(visibleSize.width / 2, 650))));

	GameData::getTextManager()->resetText();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/mainBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	return true;
}

void MainScene::setStartPane()
{
	auto StartButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("StartButton");
	auto SettingButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("SettingButton");
	auto mainContentPane = getChildByName<CCSprite*>("mainContentPane");
	auto mainSettingPane = getChildByName<CCSprite*>("mainSettingPane");
	auto NewStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("NewStartButton");
	auto ContinueStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("ContinueStartButton");
	auto BGMButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("BGMButton");
	auto EffectButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("EffectButton");

	StartButton->stopAllActions();
	StartButton->runAction(ScaleTo::create(0.2f, 1.1f));
	StartButton->runAction(MoveTo::create(0.2f, Vec2(360, 420)));
	SettingButton->stopAllActions();
	SettingButton->runAction(ScaleTo::create(0.2f, 1.0f));
	SettingButton->runAction(MoveTo::create(0.2f, Vec2(380, 300)));
	mainContentPane->stopAllActions();
	mainContentPane->runAction(MoveTo::create(0.4f, Vec2(144, 280)));
	mainSettingPane->stopAllActions();
	mainSettingPane->runAction(MoveTo::create(0.4f, Vec2(-144, 280)));
	NewStartButton->setEnabled(true);
	ContinueStartButton->setEnabled(true);
	BGMButton->setEnabled(false);
	EffectButton->setEnabled(false);
}

void MainScene::setSettingPane()
{
	auto StartButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("StartButton");
	auto SettingButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("SettingButton");
	auto mainContentPane = getChildByName<CCSprite*>("mainContentPane");
	auto mainSettingPane = getChildByName<CCSprite*>("mainSettingPane");
	auto NewStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("NewStartButton");
	auto ContinueStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("ContinueStartButton");
	auto BGMButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("BGMButton");
	auto EffectButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("EffectButton");

	StartButton->stopAllActions();
	StartButton->runAction(ScaleTo::create(0.2f, 1.0f));
	StartButton->runAction(MoveTo::create(0.2f, Vec2(380, 420)));
	SettingButton->stopAllActions();
	SettingButton->runAction(ScaleTo::create(0.2f, 1.1f));
	SettingButton->runAction(MoveTo::create(0.2f, Vec2(360, 300)));
	mainContentPane->stopAllActions();
	mainContentPane->runAction(MoveTo::create(0.4f, Vec2(-144, 280)));
	mainSettingPane->stopAllActions();
	mainSettingPane->runAction(MoveTo::create(0.4f, Vec2(144, 280)));
	NewStartButton->setEnabled(false);
	ContinueStartButton->setEnabled(false);
	BGMButton->setEnabled(true);
	EffectButton->setEnabled(true);
	
}

void MainScene::createToastLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//텍스트 불러오기
	GameData::getTextManager()->createText("error_nosavefile.txt");
	auto toastLayer = Layer::create();
	toastLayer->setName("toastLayer");
	toastLayer->setPosition(Point::ZERO);
	auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
	backImg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto menuPane = CCSprite::create("gfx/object/selectPane.png");
	menuPane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto menu_label = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/HoonWhitecatR.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	menu_label->setPosition(Point(200, 200));
	menu_label->setColor(Color3B::BLACK);
	auto okButton = MenuItemImage::create(
		"gfx/icon/selectButton.png",
		"gfx/icon/selectButton_clicked.png",
		CC_CALLBACK_1(MainScene::okClicked, this));
	okButton->setPosition(Vec2(200, 80));
	auto ok_label = Label::createWithTTF(GameData::getTextManager()->getTextList()->pop(), "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	ok_label->setPosition(Point(60, 40));
	ok_label->setColor(Color3B::BLACK);
	okButton->addChild(ok_label);
	auto menu = Menu::create(okButton, NULL);
	menu->setPosition(Point::ZERO);
	menuPane->addChild(menu_label);
	menuPane->addChild(menu);
	toastLayer->addChild(backImg, 0);
	toastLayer->addChild(menuPane, 1);
	addChild(toastLayer, 8);
	setMainButtonEnable(false);
}

void MainScene::setMainButtonEnable(bool b)
{
	auto StartButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("StartButton");
	auto SettingButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("SettingButton");
	auto mainContentPane = getChildByName<CCSprite*>("mainContentPane");
	auto mainSettingPane = getChildByName<CCSprite*>("mainSettingPane");
	auto NewStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("NewStartButton");
	auto ContinueStartButton = getChildByName("mainContentPane")->getChildByName("startMenu")->getChildByName<MenuItemImage*>("ContinueStartButton");
	auto BGMButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("BGMButton");
	auto EffectButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("EffectButton");
	StartButton->stopAllActions();
	StartButton->runAction(ScaleTo::create(0.2f, 1.0f));
	StartButton->runAction(MoveTo::create(0.2f, Vec2(380, 420)));
	SettingButton->stopAllActions();
	SettingButton->runAction(ScaleTo::create(0.2f, 1.0f));
	SettingButton->runAction(MoveTo::create(0.2f, Vec2(380, 300)));
	mainContentPane->stopAllActions();
	mainContentPane->setPosition(Point(-144, 280));
	mainSettingPane->stopAllActions();
	mainSettingPane->setPosition(Point(-144, 280));
	StartButton->setEnabled(b);
	SettingButton->setEnabled(b);
	NewStartButton->setEnabled(b);
	ContinueStartButton->setEnabled(b);
	BGMButton->setEnabled(b);
	EffectButton->setEnabled(b);
}

void MainScene::startClicked(cocos2d::Ref * pSender)
{
	log("start clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/clickEffect.mp3");
	}
	setStartPane();
}

void MainScene::newStartClicked(cocos2d::Ref * pSender)
{
	log("start clicked!");
	GameData::getInGameData()->setNewGameSetting(0);
	auto gameScene = CCTransitionFade::create(1.0f, PrologScene::createScene());
	Director::getInstance()->replaceScene(gameScene);
}

void MainScene::continueStartClicked(cocos2d::Ref * pSender)
{
	log("setting clicked!");
	GameData::getInGameData()->setTutoEnd(true);
	GameData::getInGameData()->setFloorNum(51);
	DatabaseManager::getInstance()->loadAllData();
	if (GameData::getInGameData()->getFloorNum() == 51) {
		createToastLayer();
	}
	else {
		auto gameScene = CCTransitionFade::create(1.0f, GameScene::createScene());
		Director::getInstance()->replaceScene(gameScene);
	}
}

void MainScene::settingClicked(cocos2d::Ref * pSender)
{
	log("setting clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/clickEffect.mp3");
	}
	setSettingPane();
}

void MainScene::BGMClicked(cocos2d::Ref * pSender)
{
	auto BGMButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("BGMButton");
	if (GameData::getGameData()->getBGM() == 0) {
		GameData::getGameData()->setBGM(10);
		BGMButton->setNormalImage(CCSprite::create("gfx/icon/audio_on.png"));
		BGMButton->setSelectedImage(CCSprite::create("gfx/icon/audio_on.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else {
		GameData::getGameData()->setBGM(0);
		BGMButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		BGMButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	DatabaseManager::getInstance()->updateSettingData();
}

void MainScene::EffectClicked(cocos2d::Ref * pSender)
{
	auto EffectButton = getChildByName("mainSettingPane")->getChildByName("settingMenu")->getChildByName<MenuItemImage*>("EffectButton");
	if (GameData::getGameData()->getEffect() == 0) {
		GameData::getGameData()->setEffect(10);
		EffectButton->setNormalImage(CCSprite::create("gfx/icon/audio_on.png"));
		EffectButton->setSelectedImage(CCSprite::create("gfx/icon/audio_on.png"));
	}
	else {
		GameData::getGameData()->setEffect(0);
		EffectButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		EffectButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
	}
	DatabaseManager::getInstance()->updateSettingData();
}

void MainScene::okClicked(cocos2d::Ref * pSender)
{
	removeChildByName("toastLayer");
	setMainButtonEnable(true);
}

void MainScene::quitClicked(cocos2d::Ref * pSender)
{
	log("quit clicked!");
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
