#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "GameData.h"
#include "GameScene.h"
#include "GameOverScene.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

bool commuOn = false;
bool canClick = true;
std::string actText[4];
int actNum[4];
int BattleScene::MAX_TUTORIAL = 7;

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	situNum = 0;
	textNum = 0;
	type = 0;
	tutorialCase = 0;
	setActText();
	setActNumber();
	auto BGImage = CCSprite::create("gfx/backGround/room0.png");
	BGImage->setTexture(GameData::getGameData()->setRoomBGImage()->getTexture());
	BGImage->setScale(2.0f);
	if(GameData::getInGameData()->getFloorNum() == 0)
		BGImage->setPosition(Point(visibleSize.width / 2 + 120, visibleSize.height / 2 + 110));
	else
		BGImage->setPosition(Point(visibleSize.width / 2 - 120, visibleSize.height / 2 + 110));
	auto battleBGDark = CCSprite::create("gfx/object/battleBGDark.png");
	battleBGDark->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    auto MonsterImage = CCSprite::create("gfx/monster/monster1.png");
	MonsterImage->setName("MonsterImage");
	MonsterImage->setAnchorPoint(Vec2(0.5, 0));
	MonsterImage->setScale(2.0f);
	MonsterImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 40));

	auto damagedEffect = CCSprite::create("gfx/object/damagedEffect.png");
	damagedEffect->setName("damagedEffect");
	damagedEffect->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	damagedEffect->setOpacity(0);
	
	auto TextPane = CCSprite::create("gfx/object/battlePane.png");
	TextPane->setName("TextPane");
	TextPane->setPosition(Point(visibleSize.width / 2, 150));
	auto text_label = Label::createWithTTF("hi", "fonts/THELeft.ttf",32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	text_label->setName("text_label");
	text_label->setPosition(Point(visibleSize.width / 2, 150));
	text_label->setColor(Color3B::BLACK);
	auto nextButton = MenuItemImage::create(
		"gfx/icon/nextText.png",
		"gfx/icon/nextText_clicked.png",
		CC_CALLBACK_1(BattleScene::nextButtonClicked, this));
	nextButton->setName("nextButton");
	nextButton->setPosition(Point(430, 50));
	nextButton->setOpacity(0);
	nextButton->setEnabled(false);
	auto nextButtonLayer = Menu::create(nextButton, NULL);
	nextButtonLayer->setName("nextButtonLayer");
	nextButtonLayer->setPosition(Point(0, 0));
	TextPane->addChild(text_label);
	TextPane->addChild(nextButtonLayer);
	TextPane->setOpacity(0);
	text_label->setOpacity(0);
	auto BattlePane = CCSprite::create("gfx/object/battlePane.png");
	BattlePane->setPosition(Point(visibleSize.width / 2, 150));
	auto selectButton1 = MenuItemImage::create(
		"gfx/icon/battleButton.png",
		"gfx/icon/battleButton_clicked.png",
		CC_CALLBACK_1(BattleScene::button1Clicked, this));
	selectButton1->setName("selectButton1");
	selectButton1->setPosition(Point(120, 225));
	auto selectButton2 = MenuItemImage::create(
		"gfx/icon/battleButton.png",
		"gfx/icon/battleButton_clicked.png",
		CC_CALLBACK_1(BattleScene::button2Clicked, this));
	selectButton2->setName("selectButton2");
	selectButton2->setPosition(Point(360, 225));
	auto selectButton3 = MenuItemImage::create(
		"gfx/icon/battleButton.png",
		"gfx/icon/battleButton_clicked.png",
		CC_CALLBACK_1(BattleScene::button3Clicked, this));
	selectButton3->setName("selectButton3");
	selectButton3->setPosition(Point(120, 75));
	auto selectButton4 = MenuItemImage::create(
		"gfx/icon/battleButton.png",
		"gfx/icon/battleButton_clicked.png",
		CC_CALLBACK_1(BattleScene::button4Clicked, this));
	selectButton4->setName("selectButton4");
	selectButton4->setPosition(Point(360, 75));
	auto backButton = MenuItemImage::create(
		"gfx/icon/back_icon.png",
		"gfx/icon/back_icon_clicked.png",
		CC_CALLBACK_1(BattleScene::backButtonClicked, this));
	backButton->setName("backButton");
	backButton->setPosition(Point(440, 340));
	backButton->setScale(0.125f);
	backButton->setOpacity(0);
	
	auto menuLayer = Menu::create(selectButton1, selectButton2, selectButton3, selectButton4, backButton, NULL);
	menuLayer->setName("menuLayer");
	menuLayer->setPosition(Point(0, 0));

	textString.str("");
	auto button1_label = Label::createWithTTF(textString.str(), "fonts/THE_Ppikkeutppikkeut.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	button1_label->setName("button1_label");
	button1_label->setPosition(Point(120, 225));
	button1_label->setColor(Color3B::BLACK);
	auto button2_label = Label::createWithTTF(textString.str(), "fonts/THE_Ppikkeutppikkeut.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	button2_label->setName("button2_label");
	button2_label->setPosition(Point(360, 225));
	button2_label->setColor(Color3B::BLACK);
	auto button3_label = Label::createWithTTF(textString.str(), "fonts/THE_Ppikkeutppikkeut.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	button3_label->setName("button3_label");
	button3_label->setPosition(Point(120, 75));
	button3_label->setColor(Color3B::BLACK);
	auto button4_label = Label::createWithTTF(textString.str(), "fonts/THE_Ppikkeutppikkeut.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	button4_label->setName("button4_label");
	button4_label->setPosition(Point(360, 75));
	button4_label->setColor(Color3B::BLACK);
	
	auto textLayer = Layer::create();
	textLayer->setName("textLayer");
	textLayer->setPosition(Point(0,0));
	textLayer->addChild(button1_label);
	textLayer->addChild(button2_label);
	textLayer->addChild(button3_label);
	textLayer->addChild(button4_label);

	auto monsterStatus = CCSprite::create("gfx/object/MonsterStatusPane.png");
	monsterStatus->setPosition(Point(visibleSize.width / 2, 750));
	auto playerStatus = CCSprite::create("gfx/object/PlayerStatusPane.png");
	playerStatus->setPosition(Point(visibleSize.width / 2, 290));
	auto monsterStatus_back = CCSprite::create("gfx/object/MonsterStatusPane_back.png");
	monsterStatus_back->setPosition(Point(visibleSize.width / 2, 750));
	auto playerStatus_back = CCSprite::create("gfx/object/PlayerStatusPane_back.png");
	playerStatus_back->setPosition(Point(visibleSize.width / 2, 290));

	auto P_HP_Gage = CCSprite::create("gfx/object/B_PHP_Gage.png");
	P_HP_Gage->setName("P_HP_Gage");
	P_HP_Gage->setAnchorPoint(Vec2(0, 0));
	P_HP_Gage->setPosition(Point(30, 302));
	auto M_HP_Gage = CCSprite::create("gfx/object/B_MHP_Gage.png");
	M_HP_Gage->setName("M_HP_Gage");
	M_HP_Gage->setAnchorPoint(Vec2(0, 0));
	M_HP_Gage->setPosition(Point(30, 762));
	auto M_Weak_Gage = CCSprite::create("gfx/object/B_Week_Gage.png");
	M_Weak_Gage->setName("M_Weak_Gage");
	M_Weak_Gage->setAnchorPoint(Vec2(0, 0));
	M_Weak_Gage->setPosition(Point(30, 735));
	P_HP_Gage->setScaleX(float(GameData::getPlayer()->getHP() / Player::MAX_HP));
	M_HP_Gage->setScaleX((float)GameData::getMapData()->getMonster()->getHP() / (float)GameData::getMapData()->getMonster()->getMAXHP());
	M_Weak_Gage->setScaleX((float)GameData::getMapData()->getMonster()->getWeak() / (float)GameData::getMapData()->getMonster()->getMAXWEAK());

	auto P_HP_label = Label::createWithTTF("", "fonts/arial.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	P_HP_label->setName("P_HP_label");
	P_HP_label->setPosition(Point(410, 318));
	P_HP_label->setColor(Color3B::WHITE);
	auto M_HP_label = Label::createWithTTF("", "fonts/arial.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	M_HP_label->setName("M_HP_label");
	M_HP_label->setPosition(Point(410, 777));
	M_HP_label->setColor(Color3B::WHITE);
	
	auto statusLayer = Layer::create();
	statusLayer->setName("statusLayer");
	statusLayer->setPosition(Point::ZERO);
	statusLayer->addChild(monsterStatus_back, 0);
	statusLayer->addChild(playerStatus_back, 0);
	statusLayer->addChild(P_HP_Gage, 1);
	statusLayer->addChild(M_HP_Gage, 1);
	statusLayer->addChild(M_Weak_Gage, 1);
	statusLayer->addChild(monsterStatus, 2);
	statusLayer->addChild(playerStatus, 2);
	statusLayer->addChild(P_HP_label, 3);
	statusLayer->addChild(M_HP_label, 3);

	addChild(BGImage, 0);
	addChild(battleBGDark, 0);
	addChild(MonsterImage, 1);
	addChild(statusLayer, 2);
	addChild(BattlePane,3);
	addChild(menuLayer,4);
	addChild(textLayer, 5);
	addChild(TextPane, 6);
	addChild(damagedEffect, 7);

	setMonsterImg();
	setSettings();
	monsterBreathAnimation();
	if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR)
		tutorialSetting(NULL);
	else
		createTextPane();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/battleBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}


	return true;
}

void BattleScene::setBattleText()
{
	auto selectButton1 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton1");
	auto selectButton2 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton2");
	auto selectButton3 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton3");
	auto selectButton4 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton4");
	auto backButton = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("backButton");
	auto nextButton = getChildByName("TextPane")->getChildByName("nextButtonLayer")->getChildByName<MenuItemImage*>("nextButton");
	auto button1_label = getChildByName("textLayer")->getChildByName<Label*>("button1_label");
	auto button2_label = getChildByName("textLayer")->getChildByName<Label*>("button2_label");
	auto button3_label = getChildByName("textLayer")->getChildByName<Label*>("button3_label");
	auto button4_label = getChildByName("textLayer")->getChildByName<Label*>("button4_label");
	switch (situNum) {
	case 0:
		//텍스트 불러오기
		GameData::getTextManager()->createText("battleScene0.txt");

		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop();
		button1_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop();
		button2_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop();
		button3_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop();
		button4_label->setString(textString.str());
		GameData::getTextManager()->resetText();
		break;
	case 1:
		//텍스트 불러오기
		GameData::getTextManager()->createText("battleScene1.txt");

		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop() + "\n(" << ((GameData::getPlayer()->getTotalHit() + 25) > 100 ? 100 : (GameData::getPlayer()->getTotalHit() + 25)) << "%)";
		button1_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop() + "\n(" << ((GameData::getPlayer()->getTotalHit() + 50) > 100 ? 100 : (GameData::getPlayer()->getTotalHit() + 50)) << "%)";
		button2_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop() + "\n(" << ((GameData::getPlayer()->getTotalHit() + 70) > 100 ? 100 : (GameData::getPlayer()->getTotalHit() + 70)) << "%)";
		button3_label->setString(textString.str());
		textString.str("");
		textString.clear();
		textString << GameData::getTextManager()->getTextList()->pop() + "\n(" << ((GameData::getPlayer()->getTotalHit() + 70) > 100 ? 100 : (GameData::getPlayer()->getTotalHit() + 70)) << "%)";
		button4_label->setString(textString.str());
		GameData::getTextManager()->resetText();
		break;
	case 2:
		button1_label->setString(actText[0]);
		button2_label->setString(actText[1]);
		button3_label->setString(actText[2]);
		button4_label->setString(actText[3]);
		break;
	default:
		textString.str("");
		textString.clear();
		textString << "";
		button1_label->setString(textString.str());
		break;
	}
	if (situNum == 0)
		backButton->setOpacity(0);
	else
		backButton->setOpacity(255);
	if (commuOn) {
		backButton->setOpacity(0);
		nextButton->setOpacity(255);
		nextButton->setEnabled(true);
		selectButton1->setEnabled(false);
		selectButton2->setEnabled(false);
		selectButton3->setEnabled(false);
		selectButton4->setEnabled(false);
	}
	else {
		nextButton->setOpacity(0);
		nextButton->setEnabled(false);
		selectButton1->setEnabled(true);
		selectButton2->setEnabled(true);
		selectButton3->setEnabled(true);
		selectButton4->setEnabled(true);
	}
}

void BattleScene::setMonsterImg()
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	switch (GameData::getMapData()->getMonster()->getType()) {
	case 0:
		MonsterImage->setTexture("gfx/monster/monster1.png");
		break;
	case 1:
        MonsterImage->setTexture("gfx/monster/monster2.png");
		break;
	case 2:
        MonsterImage->setTexture("gfx/monster/monster3.png");
		break;
	case 3:
        MonsterImage->setTexture("gfx/monster/monster4.png");
		break;
	case 4:
        MonsterImage->setTexture("gfx/monster/monster5.png");
		break;
	case 5:
        MonsterImage->setTexture("gfx/monster/monster6.png");
		break;
	case 9:
		MonsterImage->setTexture("gfx/monster/monster10.png");
		break;
	default:
		break;
	}
}

void BattleScene::setDeadMonsterImg(CCNode * node)
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	switch (GameData::getMapData()->getMonster()->getType()) {
	case 0:
		MonsterImage->setTexture("gfx/monster/monster1_dead.png");
		break;
	case 1:
		MonsterImage->setTexture("gfx/monster/monster2_dead.png");
		break;
	case 2:
		MonsterImage->setTexture("gfx/monster/monster3_dead.png");
		break;
	case 3:
		MonsterImage->setTexture("gfx/monster/monster4_dead.png");
		break;
	case 4:
		MonsterImage->setTexture("gfx/monster/monster5_dead.png");
		break;
	case 5:
		MonsterImage->setTexture("gfx/monster/monster6_dead.png");
		break;
	case 9:
		MonsterImage->setTexture("gfx/monster/monster10_dead.png");
		break;
	default:
		break;
	}
}

void BattleScene::setText() //텍스트 지정 및 몬스터 애니메이션
{
	auto text_label = getChildByName("TextPane")->getChildByName<Label*>("text_label");
	textString.str("");
	textString.clear();
	if (commuOn) {
		if (situNum == 0) { //먹을거 줬을 때
			GameData::getTextManager()->createText("battleScene3.txt");
			std::string tempText[3];
			for (int i = 0; i < 3; i++)
				tempText[i] = GameData::getTextManager()->getTextList()->pop();
			GameData::getTextManager()->resetText();

			if (GameData::getPlayer()->HasItem(GameData::getMapData()->getMonster()->getType() + 70)) { //먹을거 잇음
				textString.str(tempText[0]+"\n" + GameItem::itemNumbergetName(GameData::getMapData()->getMonster()->getType() + 70) + tempText[1]);
				GameData::getMapData()->getMonster()->setWeak(0);
				GameData::getPlayer()->deleteItemType(GameData::getMapData()->getMonster()->getType() + 70);
				monsterComuAnimation1();
			}
			else { //먹을거 없음
				textString.str(tempText[2]);
				monsterComuAnimation3();
			}
			text_label->setString(textString.str());
		}
		else if (situNum == 1) { //전투
			if (textNum == 1)
				textString.str(battle_attack(type));
			else if (textNum == 2)
				if(!isBattleEnd())
					textString.str(battle_damaged(type));
			text_label->setString(textString.str());
		}
		else if (situNum == 2) { //대화하기
			if (textNum == 1)
				textString.str(battle_week(type));
			else if (textNum == 2)
				if (!isBattleEnd())
					textString.str(battle_damaged(1));
			text_label->setString(textString.str());
		}
		else if (situNum == 4) { //몬스터 죽음
			GameData::getTextManager()->createText("battleScene4.txt");
			std::string tempText[10];
			for (int i = 0; i < 10; i++)
				tempText[i] = GameData::getTextManager()->getTextList()->pop();
			GameData::getTextManager()->resetText();

			textString << tempText[GameData::getMapData()->getMonster()->getType()];
			text_label->setString(textString.str());
		}
		else if (situNum == 5) { //몬스터 물리침
			GameData::getTextManager()->createText("battleScene5.txt");
			std::string tempText[10];
			for (int i = 0; i < 10; i++)
				tempText[i] = GameData::getTextManager()->getTextList()->pop();
			GameData::getTextManager()->resetText();

			textString << tempText[GameData::getMapData()->getMonster()->getType()];
			text_label->setString(textString.str());
		}
		else if (situNum == 6) { //도망가기 성공
			GameData::getTextManager()->createText("battleScene9.txt");
			std::string tempText[3];
			for (int i = 0; i < 3; i++)
				tempText[i] = GameData::getTextManager()->getTextList()->pop();
			GameData::getTextManager()->resetText();
			textString << tempText[0];
			text_label->setString(textString.str());
		}
		else if (situNum == 7) { //도망가기 실패
			if (textNum == 1) {
				GameData::getTextManager()->createText("battleScene9.txt");
				std::string tempText[3];
				for (int i = 0; i < 3; i++)
					tempText[i] = GameData::getTextManager()->getTextList()->pop();

				GameData::getTextManager()->resetText();
				if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR)
					textString << tempText[2];
				else
					textString << tempText[1];
			}
			else if (textNum == 2)
				if (!isBattleEnd())
					textString.str(battle_damaged(0));
			text_label->setString(textString.str());
		}
		text_label->setOpacity(0);
		text_label->runAction(FadeIn::create(0.3f));
	}
}

void BattleScene::setGageScale()
{
	auto P_HP_Gage = getChildByName<Layer*>("statusLayer")->getChildByName<CCSprite*>("P_HP_Gage");
	auto M_HP_Gage = getChildByName<Layer*>("statusLayer")->getChildByName<CCSprite*>("M_HP_Gage");
	auto M_Weak_Gage = getChildByName<Layer*>("statusLayer")->getChildByName<CCSprite*>("M_Weak_Gage");
	P_HP_Gage->runAction(ScaleTo::create(0.5f, float(GameData::getPlayer()->getHP() / Player::MAX_HP), 1));
	M_HP_Gage->runAction(ScaleTo::create(0.5f, ((float)GameData::getMapData()->getMonster()->getHP() / (float)GameData::getMapData()->getMonster()->getMAXHP()), 1));
	M_Weak_Gage->runAction(ScaleTo::create(0.5f, ((float)GameData::getMapData()->getMonster()->getWeak() / (float)GameData::getMapData()->getMonster()->getMAXWEAK()), 1));
}

void BattleScene::setGageText()
{
	auto P_HP_label = getChildByName("statusLayer")->getChildByName<Label*>("P_HP_label");
	auto M_HP_label = getChildByName("statusLayer")->getChildByName<Label*>("M_HP_label");
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getHP();
	P_HP_label->setString(textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getMapData()->getMonster()->getHP();
	M_HP_label->setString(textString.str());
}

void BattleScene::setSettings()
{
	setGageScale();
	setGageText();
	setBattleText();
}

bool BattleScene::isBattleEnd()
{
	if (GameData::getPlayer()->getHP() == 0) {
		return true;
	}
	else if (GameData::getMapData()->getMonster()->getHP() == 0) {
		return true;
	}
	else if (GameData::getMapData()->getMonster()->getWeak() == 0) {
		return true;
	}
	else
		return false;
}

void BattleScene::commuStart()
{
	auto TextPane = getChildByName<CCSprite*>("TextPane");
	auto text_label = getChildByName("TextPane")->getChildByName<Label*>("text_label");
	removeTextPane(NULL);
	TextPane->setOpacity(255);
	text_label->setOpacity(255);
	textNum = 1;
	commuOn = true;
	setText();
}

void BattleScene::commuEnd()
{
	auto TextPane = getChildByName<CCSprite*>("TextPane");
	auto text_label = getChildByName("TextPane")->getChildByName<Label*>("text_label");
	auto damagedEffect = getChildByName<CCSprite*>("damagedEffect");
	TextPane->stopAllActions();
	text_label->stopAllActions();
	damagedEffect->stopAllActions();
	damagedEffect->setOpacity(0);
	TextPane->setOpacity(0);
	text_label->setOpacity(0);
	textNum = 0;
	commuOn = false;
	createTextPane();
}

void BattleScene::setActText()
{
	int textNum = 0;
	bool bo = true;

	//텍스트 불러오기
	GameData::getTextManager()->createText("battleScene2.txt");
	std::string tempText[10];
	for (int i = 0; i < 10; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();
	GameData::getTextManager()->resetText();

	int i = 0;
	while (i<4){
	actText[i] = "";
	textNum = rand() % 10;
	bo = true;
	actText[i] = tempText[textNum];
	for (int j = 0; j < i; j++) {
	if (actText[j] == actText[i])
	bo = false;
	}
	if (bo)
	i++;
	}
	
}

void BattleScene::setActNumber()
{
	int i = 0;
	bool bo = true;
	while (i < 4) {
		bo = true;
		actNum[i] = rand() % 4;
		for (int j = 0; j < i; j++) {
			if (actNum[j] == actNum[i])
				bo = false;
		}
		if (bo)
			i++;
	}
	for (int j = 0; j < 4; j++) {
		switch (actNum[j]) {
		case 0:
			actNum[j] = 50;
			break;
		case 1:
			actNum[j] = 75;
			break;
		case 2:
			actNum[j] = 75;
			break;
		case 3:
			actNum[j] = 100;
			break;
		default:
			actNum[j] = 50;
			break;
		}
	}
	log("%d %d %d %d", actNum[0], actNum[1], actNum[2], actNum[3]);
}

void BattleScene::runAwayFromMonster()
{
	if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR) //첫 튜토리얼 시
		situNum = 7; //무조건 실패
	else { //튜토리얼이 아닐 시
		int r = rand() % 100;
		if(r > 40 + (GameData::getMapData()->getMonster()->getType()*5) + (GameData::getInGameData()->getLevel()*10))
			situNum = 6;
		else
			situNum = 7;
	}
	type = 0;
	commuStart();
	setSettings();
}

void BattleScene::setButtonEnable(bool b)
{
	auto selectButton1 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton1");
	auto selectButton2 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton2");
	auto selectButton3 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton3");
	auto selectButton4 = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("selectButton4");
	auto backButton = getChildByName("menuLayer")->getChildByName<MenuItemImage*>("backButton");
	if (b) {
		selectButton1->setEnabled(true);
		selectButton2->setEnabled(true);
		selectButton3->setEnabled(true);
		selectButton4->setEnabled(true);
		backButton->setEnabled(true);
		setSettings();
	}
	else {
		selectButton1->setEnabled(false);
		selectButton2->setEnabled(false);
		selectButton3->setEnabled(false);
		selectButton4->setEnabled(false);
		backButton->setEnabled(false);
	}
}

void BattleScene::createTextPane()
{
	log("createTextPane");
	auto textPaneLayer = Layer::create();
	textPaneLayer->setName("textPaneLayer");
	textPaneLayer->setPosition(Point::ZERO);

	auto contentLabel = Label::createWithTTF("내용", "fonts/THE_Oegyeinseolmyeongseo.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	contentLabel->setName("contentLabel");
	contentLabel->setPosition(Point(240, 80));
	contentLabel->setColor(Color3B::WHITE);

	auto heartImg = CCSprite::create("gfx/player/heart_battle.png");
	heartImg->setName("heartImg");
	heartImg->setPosition(Point(40, 80));

	auto contentPane = CCSprite::create("gfx/object/textPane_battle.png");
	contentPane->setName("contentPane");
	contentPane->setPosition(Point(240, 680));
	contentPane->addChild(contentLabel, 0);
	contentPane->addChild(heartImg, 1);

	textPaneLayer->addChild(contentPane);
	

	addChild(textPaneLayer, 8);
	contentPane->setOpacity(0);
	contentLabel->setOpacity(0);
	heartImg->setOpacity(0);
	contentPane->runAction(FadeIn::create(0.5f));
	contentLabel->runAction(FadeIn::create(0.5f));
	heartImg->runAction(FadeIn::create(0.5f));
	setTextPane();
}

void BattleScene::setTextPane()
{
	log("setTextPane");
	CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(BattleScene::fadeOutTextPane));
	callFunc->setTag(1);
	auto heartImg = getChildByName("textPaneLayer")->getChildByName("contentPane")->getChildByName<CCSprite*>("heartImg");
	log("find heartImg");
	auto contentLabel = getChildByName("textPaneLayer")->getChildByName("contentPane")->getChildByName<Label*>("contentLabel");
	log("find contentLabel");
	GameData::getTextManager()->createText("battle_heart_first.txt");
	log("find text file");
	int r = rand() % 15;
	if (GameData::getPlayer()->getAngel() > 50)
		contentLabel->setString(GameData::getInGameData()->getTextManager()->getTextList()->getText(15));
	else
		contentLabel->setString(GameData::getInGameData()->getTextManager()->getTextList()->getText(r));
	log("insert text, random number : %d",r);
	heartImg->runAction(RepeatForever::create(Sequence::create(
			MoveBy::create(0.5f, Vec2(0, 20)),
			MoveBy::create(1.0f, Vec2(0, -40)),
			MoveBy::create(0.5f, Vec2(0, 20)),
			nullptr)));
	log("heart animation");
	this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.0f), callFunc));
}

void BattleScene::fadeOutTextPane(CCNode * node)
{
	log("fadeOutTextPane");
	if (getChildByName<Layer*>("textPaneLayer") != NULL) {
		CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(BattleScene::removeTextPane));
		getChildByName<Layer*>("textPaneLayer")->stopAllActions();
		getChildByName<Layer*>("textPaneLayer")->getChildByName("contentPane")->runAction(FadeOut::create(0.5f));
		getChildByName<Layer*>("textPaneLayer")->getChildByName("contentPane")->getChildByName<CCSprite*>("heartImg")->runAction(FadeOut::create(0.5f));
		getChildByName("textPaneLayer")->getChildByName("contentPane")->getChildByName<Label*>("contentLabel")->runAction(FadeOut::create(0.5f));
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.5f), callFunc));
	}
}

void BattleScene::removeTextPane(CCNode *node)
{
	if (getChildByName<Layer*>("textPaneLayer") != NULL) {
		getChildByName<Layer*>("textPaneLayer")->getActionManager()->removeAllActions();
		//getActionManager()->removeActionByTag(1, getChildByName<Layer*>("textPaneLayer"));
		monsterBreathAnimation();
		removeChildByName("textPaneLayer");
	}
}

void BattleScene::createCommuPane()
{
	if (GameData::getInGameData()->getFloorNum() != 50) { //튜토리얼이 아닐때
		switch (GameData::getInGameData()->getCommuCase()) { //현재상황에 맞는 텍스트파일을 불러옴
		case 0:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		case 1:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		case 2:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		case 3:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		case 4:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		default:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		}
	}
	else {
		switch (tutorialCase) { //현재상황에 맞는 텍스트파일을 불러옴
		case 0:
			GameData::getTextManager()->createText("battle_tutorial0.txt");
			break;
		case 2:
			GameData::getTextManager()->createText("battle_tutorial1.txt");
			break;
		case 4:
			GameData::getTextManager()->createText("battle_tutorial2.txt");
			break;
		case 6:
			GameData::getTextManager()->createText("battle_tutorial3.txt");
			break;
		default:
			GameData::getTextManager()->createText("battle_tutorial0.txt");
			break;
		}

	}
	auto commuLayer = Layer::create();
	commuLayer->setName("commuLayer");
	commuLayer->setPosition(Point::ZERO);
	auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
	backImg->setPosition(Point(240, 400));
	auto nextButton = MenuItemImage::create(
		"gfx/icon/nextText.png",
		"gfx/icon/nextText_clicked.png",
		CC_CALLBACK_1(BattleScene::NextTextClicked, this));
	nextButton->setName("nextButton");
	nextButton->setPosition(Point(420, 50));
	auto previousButton = MenuItemImage::create(
		"gfx/icon/previousText.png",
		"gfx/icon/previousText_clicked.png",
		CC_CALLBACK_1(BattleScene::PreviousTextClicked, this));
	previousButton->setName("previousButton");
	previousButton->setPosition(Point(60, 50));
	previousButton->setVisible(false);
	previousButton->setEnabled(false);
	auto skipButton = MenuItemImage::create(
		"gfx/icon/skip_icon.png",
		"gfx/icon/skip_icon_clicked.png",
		CC_CALLBACK_1(BattleScene::SkipClicked, this));
	skipButton->setName("skipButton");
	skipButton->setPosition(Point(400, 740));
	auto contentLabel = Label::createWithTTF("내용", "fonts/THE_Oegyeinseolmyeongseo.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	contentLabel->setName("contentLabel");
	contentLabel->setPosition(Point(230, 140));
	contentLabel->setColor(Color3B::BLACK);
	auto nameLabel = Label::createWithTTF("내용", "fonts/THE_Ppikkeutppikkeut.ttf", 34, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	nameLabel->setName("nameLabel");
	nameLabel->setPosition(Point(75, 30));
	nameLabel->setColor(Color3B::WHITE);

	auto commuMenu = Menu::create(nextButton, previousButton, skipButton, NULL);
	commuMenu->setName("commuMenu");
	commuMenu->setPosition(Point::ZERO);

	auto contextPane = CCSprite::create("gfx/object/commuPane.png");
	contextPane->setName("contextPane");
	contextPane->setPosition(Point(480, 120));
	contextPane->addChild(contentLabel);



	auto namePane = CCSprite::create("gfx/object/commuNamePane.png");
	namePane->setName("namePane");
	namePane->setPosition(Point(120, 240));
	namePane->addChild(nameLabel);

	auto charImg = CCSprite::create("gfx/player/player.png");
	charImg->setName("charImg");
	charImg->setPosition(Point(140, 300));

	commuLayer->addChild(backImg, 0);
	commuLayer->addChild(charImg, 1);
	commuLayer->addChild(contextPane, 2);
	commuLayer->addChild(namePane, 3);
	commuLayer->addChild(commuMenu, 4);

	addChild(commuLayer, 9);
	setButtonEnable(false);
	backImg->setOpacity(0);
	backImg->runAction(FadeIn::create(0.5f));
	setCommuPane();
}

void BattleScene::setCommuPane()
{
	auto contextPane = getChildByName("commuLayer")->getChildByName<CCSprite*>("contextPane");
	auto namePane = getChildByName("commuLayer")->getChildByName<CCSprite*>("namePane");
	auto charImg = getChildByName("commuLayer")->getChildByName<CCSprite*>("charImg");
	auto contentLabel = getChildByName("commuLayer")->getChildByName("contextPane")->getChildByName<Label*>("contentLabel");
	auto nameLabel = getChildByName("commuLayer")->getChildByName("namePane")->getChildByName<Label*>("nameLabel");

	contextPane->stopAllActions();
	namePane->stopAllActions();
	charImg->stopAllActions();
	if (charImg->getColor() == Color3B::BLACK)
		charImg->setColor(Color3B::WHITE);

	switch (GameData::getTextManager()->getTextNode()->getImg()) {
	case 0:
		if (GameData::getTextManager()->getTextNode()->getEffect() == 0) //일반표정
			charImg->setTexture("gfx/player/player.png");
		else if (GameData::getTextManager()->getTextNode()->getEffect() == 1) //놀란표정
			charImg->setTexture("gfx/player/player_surp.png");
		break;
	case 1:
		if (GameData::getTextManager()->getTextNode()->getEffect() == 0) //일반표정
			charImg->setTexture("gfx/player/heart.png");
		else if (GameData::getTextManager()->getTextNode()->getEffect() == 1) //놀란표정
			charImg->setTexture("gfx/player/heart_surp.png");
		else if (GameData::getTextManager()->getTextNode()->getEffect() == 9) { //???효과
			charImg->setTexture("gfx/player/heart.png");
			charImg->setColor(Color3B::BLACK);
		}
		break;
	case 2:
		charImg->setTexture("gfx/player/monster.png");
		break;
	case 3:
		charImg->setTexture("gfx/player/angel.png");
		break;
	case 4:
		charImg->setTexture("gfx/player/devil.png");
		break;
	}

	if (GameData::getTextManager()->getTextNum() % 2 == 0) { //짝수일때 왼쪽부터 시작
		namePane->setOpacity(0.2);
		namePane->setPosition(Point(100, 240));
		namePane->runAction(Spawn::create(
			FadeIn::create(0.4f),
			MoveTo::create(0.4f, Vec2(120, 240)),
			nullptr));
		charImg->setFlipX(false);
		charImg->setOpacity(0.2);
		charImg->setPosition(Point(100, 300));
		charImg->runAction(Spawn::create(
			FadeIn::create(0.6f),
			MoveTo::create(0.4f, Vec2(140, 300)),
			nullptr));
	}
	else {
		namePane->setOpacity(0.2);
		namePane->setPosition(Point(380, 240));
		namePane->runAction(Spawn::create(
			FadeIn::create(0.4f),
			MoveTo::create(0.4f, Vec2(360, 240)),
			nullptr));
		charImg->setFlipX(true);
		charImg->setOpacity(0.2);
		charImg->setPosition(Point(380, 300));
		charImg->runAction(Spawn::create(
			FadeIn::create(0.6f),
			MoveTo::create(0.4f, Vec2(340, 300)),
			nullptr));
	}
	if (GameData::getTextManager()->getTextNode()->getEffect() == 1) {
		charImg->runAction(Sequence::create(
			ScaleTo::create(0.2f, 1.1f),
			MoveBy::create(0.1f, Vec2(20, 0)),
			MoveBy::create(0.1f, Vec2(-40, 0)),
			MoveBy::create(0.1f, Vec2(40, 0)),
			MoveBy::create(0.1f, Vec2(-40, 0)),
			MoveBy::create(0.1f, Vec2(40, 0)),
			MoveBy::create(0.1f, Vec2(-20, 0)),
			ScaleTo::create(0.2f, 1.0f),
			nullptr));
	}
	else {
		charImg->setScale(1.0f);
	}

	//텍스트 불러오기
	contentLabel->setString(GameData::getTextManager()->getText());
	nameLabel->setString(GameData::getTextManager()->getTextNode()->getName());
	contextPane->setOpacity(0.2);
	contextPane->setPosition(Point(240, 100));
	contextPane->runAction(Spawn::create(
		FadeIn::create(0.3f),
		MoveTo::create(0.3f, Vec2(240, 120)),
		nullptr));

}

void BattleScene::deleteCommuPane()
{
	removeChildByName("commuLayer");
	setButtonEnable(true);
}

void BattleScene::tutorialSetting(CCNode *node)
{
	CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(BattleScene::tutorialSetting));
	CCSprite* img;
	switch (tutorialCase) {
	case 0:
		setButtonEnable(false);
		createCommuPane();
		break;
	case 1:
		setButtonEnable(false);
		img = CCSprite::create("gfx/object/arrow_up.png");
		img->setName("arrow");
		img->setPosition(Point(240, 660));
		addChild(img, 10);
		img->runAction(Sequence::create(
			MoveBy::create(0.15f, Vec2(0, -20)),
			MoveBy::create(0.3f, Vec2(0, 40)),
			MoveBy::create(0.3f, Vec2(0, -40)),
			MoveBy::create(0.3f, Vec2(0, 40)),
			MoveBy::create(0.3f, Vec2(0, -40)),
			MoveBy::create(0.3f, Vec2(0, 40)),
			MoveBy::create(0.15f, Vec2(0, -25)),
			nullptr));
		tutorialCase++;
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1.8f), callFunc));
		break;
	case 2:
		removeChildByName("arrow");
		createCommuPane();
		break;
	case 3:
		break;
	case 4: //싸워서 물리쳤을 때
		setButtonEnable(false);
		createCommuPane();
		break;
	case 5:
		GameData::getInGameData()->setTutoEnd(true);
		Director::getInstance()->replaceScene(CCTransitionFadeTR::create(0.5f, GameScene::createScene()));
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
		if (GameData::getGameData()->getBGM() == 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		break;
	case 6: //대화로 물리쳤을 때
		setButtonEnable(false);
		createCommuPane();
		break;
	case 7:
		GameData::getInGameData()->setTutoEnd(true);
		Director::getInstance()->replaceScene(CCTransitionFadeTR::create(0.5f, GameScene::createScene()));
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
		if (GameData::getGameData()->getBGM() == 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		break;
	}
}


void BattleScene::monsterBreathAnimation()
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	MonsterImage->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(1, 2.1),
			ScaleTo::create(2, 1.9),
			ScaleTo::create(1, 2.0),
			nullptr))
	);
}

void BattleScene::monsterVoidAnimation() //회피
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
			MoveBy::create(0.3f, Vec2(30, 0)),
			MoveBy::create(0.3f, Vec2(-30, 0)),
			nullptr));
}

void BattleScene::monsterDamagedAnimation() //타격입음
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Blink::create(0.5f, 2));
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/monsterAttackEffect.mp3");
	}
}

void BattleScene::monsterAttackAnimation() //공격 시
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
		JumpBy::create(0.3f, Vec2(-30, -20),20,1),
		JumpBy::create(0.3f, Vec2(30, 20), 10, 1),
		nullptr));
}

void BattleScene::monsterComuAnimation1() //매우 기뻐함
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
		JumpBy::create(0.3f, Vec2(0, 0), 30, 2),
		nullptr));
}

void BattleScene::monsterComuAnimation2() //보통
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
		SkewBy::create(0.15f, 8, 0),
		SkewBy::create(0.15f, -8, 0),
		SkewBy::create(0.15f, -8, 0),
		SkewBy::create(0.15f, 8, 0),
		nullptr));
}

void BattleScene::monsterComuAnimation3() //효과 미미
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
		MoveBy::create(0.1f, Vec2(10, 0)),
		MoveBy::create(0.1f, Vec2(-20, 0)),
		MoveBy::create(0.1f, Vec2(20, 0)),
		MoveBy::create(0.1f, Vec2(-20, 0)),
		MoveBy::create(0.1f, Vec2(20, 0)),
		MoveBy::create(0.1f, Vec2(-10, 0)),
		nullptr));
}

void BattleScene::monsterDeadAnimation()
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(Sequence::create(
		Blink::create(0.5f, 3),
		DelayTime::create(0.1f),
		CCCallFuncN::create(this, callfuncN_selector(BattleScene::setDeadMonsterImg)),
		nullptr));
}

void BattleScene::monsterHappyAnimation()
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	//MonsterImage->stopAllActions();
	MonsterImage->runAction(RepeatForever::create(
		Sequence::create(
			JumpBy::create(0.3f, Vec2(0, 0), 30, 1),
			DelayTime::create(0.3f),
			nullptr))
	);
}

void BattleScene::playerDamagedEffect()
{
	auto damagedEffect = getChildByName<CCSprite*>("damagedEffect");
	damagedEffect->runAction(Sequence::create(
		DelayTime::create(0.3f),
		FadeIn::create(0.15f),
		FadeOut::create(0.15f),
		nullptr));
}

std::string BattleScene::battle_attack(int t)
{
	std::ostringstream textString;
	int per, damage = 0;
	textString.str("");
	textString.clear();
	//텍스트 불러오기
	GameData::getTextManager()->createText("battleScene6.txt");
	std::string tempText[8];
	for (int i = 0; i < 8; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();
	GameData::getTextManager()->resetText();

	if (t == 0)
		per = 25;
	else if (t == 1)
		per = 50;
	else if (t == 2)
		per = 70;
	else
		per = 70;
	per += GameData::getPlayer()->getTotalHit();
	damage = sumDamage(t, GameData::getPlayer()->getTotalAttack(), GameData::getMapData()->getMonster()->getDepence());
	int r = rand() % 100;
	if (per >= r) { //공격 성공
		textString << tempText[0] << damage << tempText[1] << "\n" << tempText[2];
		GameData::getMapData()->getMonster()->getDamaged(damage);
		monsterDamagedAnimation();
		if (type == 2) {
			if (GameData::getMapData()->getMonster()->getDepence() > 2) {
				GameData::getMapData()->getMonster()->setDepence(GameData::getMapData()->getMonster()->getDepence() - 1);
				textString << "\n" << tempText[3];
			}
			else
				textString << "\n" << tempText[4];
		}
		else if (type == 3) {
			if (GameData::getMapData()->getMonster()->getAttack() > 2) {
				GameData::getMapData()->getMonster()->setAttack(GameData::getMapData()->getMonster()->getAttack() - 1);
				textString << "\n" << tempText[5];
			}
			else
				textString << "\n" << tempText[6];
		}
	}
	else {
		monsterVoidAnimation();
		textString << tempText[7];
	}
	return textString.str();
}

std::string BattleScene::battle_week(int t) //대화하기 공격
{
	std::ostringstream textString;
	int damage = 0;
	textString.str("");
	textString.clear();
	//텍스트 불러오기
	GameData::getTextManager()->createText("battleScene8.txt");
	std::string tempText[4];
	for (int i = 0; i < 4; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();
	GameData::getTextManager()->resetText();

	damage = (float)GameData::getPlayer()->getTotalCommuPower() * ((float)actNum[t] / 100.0f);
	if (damage != 0) {
		if (actNum[t] == 100) {
			textString << tempText[0];
			setActText();
			setActNumber();
			monsterComuAnimation1();
		}
		else if (actNum[t] == 75) {
			textString << tempText[1];
			monsterComuAnimation2();
		}
		else {
			textString << tempText[2];
			monsterComuAnimation3();
		}
		GameData::getMapData()->getMonster()->getWeakDamaged(damage);
	}
	else
		textString << tempText[3];
	return textString.str();
}

std::string BattleScene::battle_damaged(int t)
{
	std::ostringstream textString;
	int per, damage = 0;
	textString.str("");
	textString.clear();
	//텍스트 불러오기
	GameData::getTextManager()->createText("battleScene7.txt");
	std::string tempText[4];
	for (int i = 0; i < 4; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();
	GameData::getTextManager()->resetText();

	if (t == 0)
		per = 90;
	else if (t == 1)
		per = 95;
	else if (t == 2)
		per = 100;
	else
		per = 100;
	per -= GameData::getPlayer()->getTotalEva();
	damage = sumDamage(1, GameData::getMapData()->getMonster()->getAttack(), GameData::getPlayer()->getTotalDepence());
	int r = rand() % 100;
	monsterAttackAnimation();
	if (per >= r) { //공격 성공
		textString << tempText[0] << damage << tempText[1] << "\n" << tempText[2];
		GameData::getPlayer()->getDamaged(damage);
		playerDamagedEffect();
		if (GameData::getGameData()->getEffect() > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/punchingEffect.mp3");
		}
	}
	else {
		textString << tempText[3];
	}
	return textString.str();
}

int BattleScene::sumDamage(int type, int at, int de)
{
	float result = at;
	result -= at * de / 30;
	if (type == 0)
		result *= 1.5;
	else if (type == 1)
		result *= 1;
	else if (type == 2)
		result *= 0.5;
	else if (type == 3)
		result *= 0.5;
	return (int)result;
}


void BattleScene::button1Clicked(cocos2d::Ref * pSender)
{
	log("button1 clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
	}
	if (situNum == 0) {
		situNum = 1;
	}
	else if (situNum == 1) {
		type = 0;
		commuStart();
	}
	else if (situNum == 2) {
		type = 0;
		commuStart();
	}
	setSettings();
}

void BattleScene::button2Clicked(cocos2d::Ref * pSender)
{
	log("button2 clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
	}
	if (situNum == 0) {
		commuStart();
	}
	else if (situNum == 1) {
		type = 1;
		commuStart();
	}
	else if (situNum == 2) {
		type = 1;
		commuStart();
	}
	setSettings();
}

void BattleScene::button3Clicked(cocos2d::Ref * pSender)
{
	log("button3 clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
	}
	if (situNum == 0) {
		situNum = 2;
	}
	else if (situNum == 1) {
		type = 2;
		commuStart();
	}
	else if (situNum == 2) {
		type = 2;
		commuStart();
	}
	setSettings();
}

void BattleScene::button4Clicked(cocos2d::Ref * pSender)
{
	log("button4 clicked!");
	if (GameData::getGameData()->getEffect() > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
	}
	if (situNum == 0) { //나가기 클릭
		runAwayFromMonster();
	}
	else if (situNum == 1) {
		type = 3;
		commuStart();
	}
	else if (situNum == 2) {
		type = 3;
		commuStart();
	}
	setSettings();
}

void BattleScene::backButtonClicked(cocos2d::Ref * pSender)
{
	log("backButton clicked!");
	if (situNum > 0) {
		situNum = 0;
		setSettings();
	}
}

void BattleScene::nextButtonClicked(cocos2d::Ref * pSender)
{
	log("nextButton clicked!");
	if (commuOn) { //대화창 열린상태
		if (situNum == 0) {
			if (textNum < 2) {
				textNum++;
				situNum = 2;
				setText();
			}
			else {
				situNum = 0;
				type = 0;
				commuEnd();
			}
			if (isBattleEnd()) {
				situNum = 5;
				setText();
			}
			setSettings();
			if (isBattleEnd()) {
				if (GameData::getPlayer()->getHP() == 0) { //게임오버
					DatabaseManager::getInstance()->saveAllData();
					Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, GameOverScene::createScene()));
				}
				else if (GameData::getMapData()->getMonster()->getHP() == 0) { //몬스터 사망시
					situNum = 4;
					setText();
					monsterDeadAnimation();
				}
				else if (GameData::getMapData()->getMonster()->getWeak() == 0) { //몬스터 순화시
					situNum = 5;
					setText();
					monsterHappyAnimation();
				}
			}
		}
		else if (situNum == 1 || situNum == 2) {
			if (textNum < 2) {
				textNum++;
				setText();
			}
			else {
				situNum = 0;
				type = 0;
				commuEnd();
			}
			setSettings();
			if (isBattleEnd()) {
				if (GameData::getPlayer()->getHP() == 0) { //게임오버
					DatabaseManager::getInstance()->saveAllData();
					Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, GameOverScene::createScene()));
				}
				else if (GameData::getMapData()->getMonster()->getHP() == 0) { //몬스터 사망시
					situNum = 4;
					setText();
					monsterDeadAnimation();
				}
				else if (GameData::getMapData()->getMonster()->getWeak() == 0) { //몬스터 순화시
					situNum = 5;
					setText();
					monsterHappyAnimation();
				}
			}
		}
		else if (situNum == 4) { //몬스터 사망 시
			situNum = 0;
			type = 0;
			commuEnd();
			setSettings();
			GameData::getPlayer()->addDevil(1+GameData::getMapData()->getMonster()->getType());
			GameData::getInGameData()->addMonsterKill();
			if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < BattleScene::MAX_TUTORIAL) {
				tutorialCase = 4;
				removeChildByName("textPaneLayer");
				tutorialSetting(NULL);
			}
			else {
				auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
				Director::getInstance()->replaceScene(GameScene);
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
				if (GameData::getGameData()->getBGM() == 0) {
					CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				}
			}
		}
		else if (situNum == 5) { //몬스터 순화 시
			situNum = 0;
			type = 0;
			commuEnd();
			setSettings();
			GameData::getPlayer()->addAngel(5);
			if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < BattleScene::MAX_TUTORIAL) {
				tutorialCase = 6;
				removeChildByName("textPaneLayer");
				tutorialSetting(NULL);
			}
			else {
				auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
				Director::getInstance()->replaceScene(GameScene);
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
				if (GameData::getGameData()->getBGM() == 0) {
					CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				}
			}
		}
		else if (situNum == 6) { //탈출 성공
			commuEnd();
			setSettings();
			DatabaseManager::getInstance()->saveAllData();
			auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
			Director::getInstance()->replaceScene(GameScene);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/gameBGM.mp3", true);
			if (GameData::getGameData()->getBGM() == 0) {
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
		}
		else if (situNum == 7) { //탈출 실패
			if (textNum < 2) {
				textNum++;
				setText();
			}
			else {
				situNum = 0;
				type = 0;
				commuEnd();
			}
			setSettings();
		}
	}
}

	void BattleScene::NextTextClicked(cocos2d::Ref * pSender)
	{
		log("next button clicked!");
		if (GameData::getInGameData()->getCommuNum() == GameData::getInGameData()->getTextManager()->getTextList()->lastNodeNum()) {
			GameData::getInGameData()->setCommuCase(0);
			GameData::getInGameData()->setCommuNum(0);
			deleteCommuPane();
			if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < BattleScene::MAX_TUTORIAL) {
				tutorialCase++;
				tutorialSetting(NULL);
			}
		}
		else {
			if (GameData::getGameData()->getEffect() > 0) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
			}
			GameData::getInGameData()->nextText();
			if (GameData::getInGameData()->getCommuNum() > 0) {
				auto previousButton = getChildByName("commuLayer")->getChildByName("commuMenu")->getChildByName<MenuItemImage*>("previousButton");
				previousButton->setVisible(true);
				previousButton->setEnabled(true);
			}
			setCommuPane();
		}
	}

	void BattleScene::PreviousTextClicked(cocos2d::Ref * pSender)
	{
		log("previous button clicked!");
		if (GameData::getGameData()->getEffect() > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
		}
		GameData::getInGameData()->previousText();
		if (GameData::getInGameData()->getCommuNum() == 0) {
			auto previousButton = getChildByName("commuLayer")->getChildByName("commuMenu")->getChildByName<MenuItemImage*>("previousButton");
			previousButton->setVisible(false);
			previousButton->setEnabled(false);
		}
		setCommuPane();
	}

	void BattleScene::SkipClicked(cocos2d::Ref * pSender)
	{
		log("skip button clicked!");
		GameData::getInGameData()->setCommuCase(0);
		GameData::getInGameData()->setCommuNum(0);
		deleteCommuPane();
		if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < BattleScene::MAX_TUTORIAL) {
			tutorialCase++;
			tutorialSetting(NULL);
		}
	}