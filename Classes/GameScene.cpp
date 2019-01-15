#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "ItemScene.h"
#include "BattleScene.h"
#include "EventScene.h"
#include "GameData.h"
#include "MainScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

int GameScene::MAX_TUTORIAL = 10;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	for (int i = 0; i < 4; i++)
		itemTypeList[i] = 100;
	//GameData::getInGameData()->setFloorNum(1);
	itemAniNum = 0;
	tutorialCase = 0;
	cancelNum = 0;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	canClick = true;
	//배경이미지
	auto BGImage = CCSprite::create("gfx/backGround/game_bg.png");
	BGImage->setName("BGImage");
	BGImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 400));
	Size BGsize = BGImage->getContentSize();
	auto building = CCSprite::create("gfx/backGround/building_bg.png");
	building->setName("building");
	building->setScale(1.15f);
	building->setPosition(Point(BGsize.width / 2, BGsize.height / 2));
	auto bgBuilding1 = CCSprite::create("gfx/backGround/game_bg_b1.png");
	bgBuilding1->setName("bgBuilding1");
	bgBuilding1->setPosition(Point(BGsize.width / 2, BGsize.height / 2 - 400));
	auto bgBuilding2 = CCSprite::create("gfx/backGround/game_bg_b2.png");
	bgBuilding2->setName("bgBuilding2");
	bgBuilding2->setPosition(Point(BGsize.width / 2, BGsize.height / 2 - 800));
	auto blackScreen = CCSprite::create("gfx/backGround/blackScreen.png");
	blackScreen->setName("blackScreen");
	blackScreen->setOpacity(0);
	blackScreen->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	blackScreen->setScale(2.0f);

	auto cloudLayer = Layer::create();
	cloudLayer->setPosition(Point(visibleSize.width, visibleSize.height / 2 + 500));
	auto cloud1 = CCSprite::create("gfx/backGround/mainBG_cloud.png");
	auto cloud2 = CCSprite::create("gfx/backGround/mainBG_cloud.png");
	cloud1->setPosition(Point(0, 400));
	cloud2->setPosition(Point(960, 400));
	cloudLayer->addChild(cloud1);
	cloudLayer->addChild(cloud2);

	BGImage->addChild(cloudLayer, 0);
	BGImage->addChild(bgBuilding1, 1);
	BGImage->addChild(bgBuilding2, 2);
	BGImage->addChild(building,3);

	
	auto roomBG = CCSprite::create("gfx/backGround/room0.png");
	roomBG->setName("roomBG");
	roomBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto roomBorder = CCSprite::create("gfx/backGround/room_border.png");
	roomBorder->setName("roomBorder");
	roomBorder->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto HP_Gage = CCSprite::create("gfx/object/HP_Gage.png");
	HP_Gage->setName("HP_Gage");
	HP_Gage->setAnchorPoint(Vec2(0,0));
	HP_Gage->setPosition(Point(25, 65));
	auto Hunger_Gage = CCSprite::create("gfx/object/Hunger_Gage.png");
	Hunger_Gage->setName("Hunger_Gage");
	Hunger_Gage->setAnchorPoint(Vec2(0, 0));
	Hunger_Gage->setPosition(Point(25, 40));
	auto Devil_Gage = CCSprite::create("gfx/object/Devil_Gage.png");
	Devil_Gage->setName("Devil_Gage");
	Devil_Gage->setAnchorPoint(Vec2(0, 0));
	Devil_Gage->setPosition(Point(25, 15));
	auto Angel_Gage = CCSprite::create("gfx/object/Angel_Gage.png");
	Angel_Gage->setName("Angel_Gage");
	Angel_Gage->setAnchorPoint(Vec2(0, 0));
	Angel_Gage->setPosition(Point(25, 15));
	HP_Gage->setScaleX(float(GameData::getPlayer()->getHP() / Player::MAX_HP));
	Hunger_Gage->setScaleX((float)GameData::getPlayer()->getHunger() / Player::MAX_HUNGER);
	Devil_Gage->setScaleX((float(GameData::getPlayer()->getDevil() / 100.0f)));
	Angel_Gage->setScaleX((float(GameData::getPlayer()->getAngel() / 100.0f)));
	
	

	auto getItemImage = CCSprite::create("gfx/item/screw.png");
	getItemImage->setName("getItemImage");
	getItemImage->setScale(0.5f);
	getItemImage->setPosition(Point(200, 400));
	getItemImage->setOpacity(0);

	//문 이미지 생성
	auto LeftDoorImage = CCSprite::create("gfx/object/door_l.png");
	LeftDoorImage->setName("LeftDoorImage");
	auto RightDoorImage = CCSprite::create("gfx/object/door_r.png");
	RightDoorImage->setName("RightDoorImage");
	LeftDoorImage->setPosition(Point(visibleSize.width / 4, visibleSize.height / 2 + 20));
	RightDoorImage->setPosition(Point(visibleSize.width / 4 * 3, visibleSize.height / 2 + 20));
	RightDoorImage->setCascadeOpacityEnabled(true);
	LeftDoorImage->setCascadeOpacityEnabled(true);

	//캐릭터이미지 및 애니메이션
	auto playerCache = CCSpriteFrameCache::getInstance();
	playerCache->addSpriteFramesWithFile("gfx/player/player_image.plist");
	
	char str[100] = { 0 };
	for (int i = 0; i < 16; i++) {
		sprintf(str, "player%02d.png", i);
		auto frame = playerCache->getSpriteFrameByName(str);
		if (i / 4 == 0)
			playerRightStandF.pushBack(frame);
		else if (i / 4 == 1)
			playerLeftStandF.pushBack(frame);
		else if (i / 4 == 2)
			playerRightRunF.pushBack(frame);
		else if (i / 4 == 3)
			playerLeftRunF.pushBack(frame);
	}
	auto playerImage = CCSprite::createWithSpriteFrameName("player00.png");
	playerImage->setName("playerImage");
	auto MonsterImage = CCSprite::create("gfx/monster/monster1.png");
	MonsterImage->setName("MonsterImage");
	MonsterImage->setAnchorPoint(Vec2(0.5, 0));

	
	//메뉴설정
	auto LeftClickButton = MenuItemImage::create(
		"gfx/icon/left_icon.png",
		"gfx/icon/left_icon_clicked.png",
		CC_CALLBACK_1(GameScene::LeftClicked, this));
	LeftClickButton->setName("LeftClickButton");
	LeftClickButton->setScale(0.75f);
	LeftClickButton->setPosition(Point(36, visibleSize.height / 2));
	auto RightClickButton = MenuItemImage::create(
		"gfx/icon/right_icon.png",
		"gfx/icon/right_icon_clicked.png",
		CC_CALLBACK_1(GameScene::RightClicked, this));
	RightClickButton->setName("RightClickButton");
	RightClickButton->setScale(0.75f);
	RightClickButton->setPosition(Point(visibleSize.width - 36, visibleSize.height / 2));
	auto DownStairButton = MenuItemImage::create(
		"gfx/icon/down_icon.png",
		"gfx/icon/down_icon_clicked.png",
		CC_CALLBACK_1(GameScene::NextClicked, this));
	DownStairButton->setName("DownStairButton");
	DownStairButton->setPosition(Point(350, 60));
	auto ItemButton = MenuItemImage::create(
		"gfx/icon/bag_icon.png",
		"gfx/icon/bag_icon_clicked.png",
		CC_CALLBACK_1(GameScene::ItemClicked, this));
	ItemButton->setName("ItemButton");
	ItemButton->setPosition(Point(96,96));
	auto BattleButton = MenuItemImage::create(
		"gfx/icon/battle_icon.png",
		"gfx/icon/battle_icon_clicked.png",
		CC_CALLBACK_1(GameScene::BattleClicked, this));
	BattleButton->setName("BattleButton");
	BattleButton->setPosition(Point(303, 180));
	auto PharmButton = MenuItemImage::create(
		"gfx/icon/pharm_icon.png",
		"gfx/icon/pharm_icon_clicked.png",
		CC_CALLBACK_1(GameScene::PharmingClicked, this));
	PharmButton->setName("PharmButton");
	PharmButton->setPosition(Point(303, 180));
	auto EventButton = MenuItemImage::create(
		"gfx/icon/event_icon.png",
		"gfx/icon/event_icon_clicked.png",
		CC_CALLBACK_1(GameScene::EventClicked, this));
	EventButton->setName("EventButton");
	EventButton->setPosition(Point(303, 180));
	auto MenuButton = MenuItemImage::create(
		"gfx/icon/menu_icon.png",
		"gfx/icon/menu_icon_clicked.png",
		CC_CALLBACK_1(GameScene::MenuClicked, this));
	MenuButton->setName("MenuButton");
	MenuButton->setPosition(Point(411, 740));
	

	auto pMenu = Menu::create(LeftClickButton, RightClickButton, DownStairButton,
		ItemButton, PharmButton, BattleButton, EventButton, MenuButton, NULL);
	pMenu->setName("pMenu");
	pMenu->setPosition(Point(0, 0));

	auto statusImage = CCSprite::create("gfx/object/statusPane.png");
	statusImage->setName("statusImage");
	statusImage->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto floorBox = CCSprite::create("gfx/object/floorBox.png");
	floorBox->setName("floorBox");
	floorBox->setPosition(Point(270, 740));
	floorBox->setScaleX(1.5f);
	auto Floor_label = Label::createWithTTF("", "fonts/HoonWhitecatR.ttf", 48, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	Floor_label->setName("Floor_label");
	Floor_label->setPosition(Point(52,45));
	Floor_label->setScaleX(0.7f);
	floorBox->addChild(Floor_label);

	auto HP_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	HP_label->setName("HP_label");
	HP_label->setPosition(Point(150, 75));
	HP_label->setColor(Color3B::BLACK);
	auto Hunger_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	Hunger_label->setName("Hunger_label");
	Hunger_label->setPosition(Point(150, 50));
	Hunger_label->setColor(Color3B::BLACK);
	auto DA_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	DA_label->setName("DA_label");
	DA_label->setPosition(Point(150, 25));
	DA_label->setColor(Color3B::BLACK);

	auto statBox = CCSprite::create("gfx/object/statusBox.png");
	statBox->setName("statBox");
	statBox->setPosition(Point(105, 740));
	auto gageBar1 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar1->setScaleX(1.2f);
	gageBar1->setPosition(Point(75, 75));
	auto gageBar2 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar2->setScaleX(1.2f);
	gageBar2->setPosition(Point(75, 50));
	auto gageBar3 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar3->setScaleX(1.2f);
	gageBar3->setPosition(Point(75, 25));

	statusImage->addChild(floorBox, 1);
	statBox->addChild(HP_Gage, 1);
	statBox->addChild(Hunger_Gage, 1);
	statBox->addChild(Devil_Gage, 1);
	statBox->addChild(Angel_Gage, 1);
	statBox->addChild(gageBar1, 2);
	statBox->addChild(gageBar2, 2);
	statBox->addChild(gageBar3, 2);
	statBox->addChild(HP_label, 3);
	statBox->addChild(Hunger_label, 3);
	statBox->addChild(DA_label, 3);

	this->addChild(BGImage, 0); //0
	this->addChild(roomBG, 1); //1
	this->addChild(RightDoorImage, 2); //2
	this->addChild(LeftDoorImage, 2); //2
	this->addChild(playerImage, 3); //3
	this->addChild(MonsterImage, 3); //3
	this->addChild(roomBorder, 4);
	this->addChild(getItemImage, 4); //3
	this->addChild(statusImage, 4); //4
	this->addChild(statBox, 5); //5
	this->addChild(pMenu, 6); //6
	addChild(blackScreen, 7); //7

	SceneLoad(); //저장된 데이터를 기반으로 씬을 불러옴
	setText();
	setGageScale();

	if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR && !GameData::getInGameData()->getTutoEnd()) {
		GameData::getInGameData()->getMapData()->addMonster(9);
		DownStairButton->setVisible(false);
		tutorialSetting(NULL);
	}

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

	return true;
}

void GameScene::SceneLoad()
{
	auto building = getChildByName("BGImage")->getChildByName<CCSprite*>("building");
	auto bgBuilding1 = getChildByName("BGImage")->getChildByName<CCSprite*>("bgBuilding1");
	auto bgBuilding2 = getChildByName("BGImage")->getChildByName<CCSprite*>("bgBuilding2");
	auto roomBG = getChildByName<CCSprite*>("roomBG");
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	auto LeftDoorImage = getChildByName<CCSprite*>("LeftDoorImage");
	auto RightDoorImage = getChildByName<CCSprite*>("RightDoorImage");
	auto LeftClickButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("LeftClickButton");
	auto RightClickButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("RightClickButton");
	auto DownStairButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("DownStairButton");
	auto PharmButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("PharmButton");
	auto BattleButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("BattleButton");
	auto EventButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("EventButton");
	//층 높이 수정
	if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR) {
		building->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 300));
		bgBuilding1->setPositionY(300);
		bgBuilding2->setPositionY(100);
		DownStairButton->setVisible(true);
		DownStairButton->setEnabled(true);
	}
	else if (GameData::getInGameData()->getFloorNum() == 1) {
		building->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 1100));
		bgBuilding1->setPositionY(1500);
		bgBuilding2->setPositionY(1500);
		DownStairButton->setVisible(false);
		DownStairButton->setEnabled(false);
	}
	else {
		building->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 800));
		bgBuilding1->setPositionY(300+ ((50-GameData::getInGameData()->getFloorNum())*15));
		if(GameData::getInGameData()->getFloorNum() < 30)
			bgBuilding2->setPositionY(100 + ((30 - GameData::getInGameData()->getFloorNum()) * 40));
	}
	//방배경 설정
	roomBG->setTexture(GameData::getGameData()->setRoomBGImage()->getTexture());

	//아이템 획득 버튼 설정
	if (GameData::getMapData()->getIsItemParm()) {
		if (GameData::getMapData()->HasMonster()) {
			EventButton->setVisible(false);
			EventButton->setEnabled(false);
			if (GameData::getMapData()->getMonster()->getHP() == 0) {
				PharmButton->setVisible(true);
				PharmButton->setEnabled(true);
				BattleButton->setVisible(false);
				BattleButton->setEnabled(false);
			}
			else if (GameData::getMapData()->getMonster()->getWeak() == 0) {
				PharmButton->setVisible(true);
				PharmButton->setEnabled(true);
				BattleButton->setVisible(false);
				BattleButton->setEnabled(false);
			}
			else {
				PharmButton->setVisible(false);
				PharmButton->setEnabled(false);
				BattleButton->setVisible(true);
				BattleButton->setEnabled(true);
			}
		}
		else {
			BattleButton->setVisible(false);
			BattleButton->setEnabled(false);
			if (GameData::getMapData()->getType() >= 3 && GameData::getMapData()->getType() <= 5) { //대화버튼 활성화
				if (GameData::getMapData()->getIsItemParm()) {
					EventButton->setVisible(true);
					EventButton->setEnabled(true);
					PharmButton->setVisible(false);
					PharmButton->setEnabled(false);
				}
			}
			else {
				if (GameData::getInGameData()->getFloorNum() == 1) { //엔딩씬
					EventButton->setVisible(true);
					EventButton->setEnabled(true);
					PharmButton->setVisible(false);
					PharmButton->setEnabled(false);
					EventButton->setNormalImage(CCSprite::create("gfx/icon/ending_icon.png"));
					EventButton->setSelectedImage(CCSprite::create("gfx/icon/ending_icon_clicked.png"));
				}
				else{
					EventButton->setVisible(false);
					EventButton->setEnabled(false);
					PharmButton->setVisible(true);
					PharmButton->setEnabled(true);
				}
			}
		}
	}
	else {
		PharmButton->setVisible(false);
		PharmButton->setEnabled(false);
		BattleButton->setVisible(false);
		BattleButton->setEnabled(false);
		EventButton->setVisible(false);
		EventButton->setEnabled(false);
		//EventButton->setVisible(true); //이벤트씬 테스트용
		//EventButton->setEnabled(true);
	}

	//방에 맞는 문 설정 및 버튼 설정
	if (GameData::getInGameData()->getFloorNum() != GameData::MAX_FLOOR && GameData::getInGameData()->getFloorNum() != 1) {
		if (GameData::getInGameData()->getRoomNum() == 0) {
			GameData::getPlayer()->setDirect(2);
			LeftClickButton->setVisible(false);
			LeftClickButton->setEnabled(false);
			RightClickButton->setVisible(true);
			RightClickButton->setEnabled(true);
			DownStairButton->setVisible(false);
			DownStairButton->setEnabled(false);
			RightDoorImage->setOpacity(255);
			LeftDoorImage->setOpacity(0);
			RightClickButton->runAction(RepeatForever::create(
				Sequence::create(
					ScaleTo::create(0.5f, 0.65f),
					ScaleTo::create(0.5f, 0.75f),
					nullptr)));
		}
		else if (GameData::getInGameData()->getRoomNum() == 2) {
			LeftClickButton->setVisible(true);
			LeftClickButton->setEnabled(true);
			RightClickButton->setVisible(false);
			RightClickButton->setEnabled(false);
			DownStairButton->setVisible(false);
			DownStairButton->setEnabled(false);
			LeftDoorImage->setOpacity(255);
			RightDoorImage->setOpacity(0);
			LeftClickButton->runAction(RepeatForever::create(
				Sequence::create(
					ScaleTo::create(0.5f, 0.65f),
					ScaleTo::create(0.5f, 0.75f),
					nullptr)));
		}
		else {
			LeftClickButton->setVisible(true);
			LeftClickButton->setEnabled(true);
			RightClickButton->setVisible(true);
			RightClickButton->setEnabled(true);
			if (GameData::getMapData()->HasMonster()) {
				if (GameData::getMapData()->getMonster()->getHP() == 0 || GameData::getMapData()->getMonster()->getWeak() == 0) {
					DownStairButton->setVisible(true);
					DownStairButton->setEnabled(true);
				}
				else {
					DownStairButton->setVisible(false);
					DownStairButton->setEnabled(false);
				}
			}
			else {
				DownStairButton->setVisible(true);
				DownStairButton->setEnabled(true);
			}
			RightDoorImage->setOpacity(255);
			LeftDoorImage->setOpacity(255);
			LeftClickButton->runAction(RepeatForever::create(
				Sequence::create(
					ScaleTo::create(0.5f, 0.65f),
					ScaleTo::create(0.5f, 0.75f),
					nullptr)));
			RightClickButton->runAction(RepeatForever::create(
				Sequence::create(
					ScaleTo::create(0.5f, 0.65f),
					ScaleTo::create(0.5f, 0.75f),
					nullptr)));
		}
	}
	else {
		LeftClickButton->setVisible(false);
		LeftClickButton->setEnabled(false);
		RightClickButton->setVisible(false);
		RightClickButton->setEnabled(false);
		if (GameData::getInGameData()->getFloorNum() == GameData::MAX_FLOOR) {
			if (GameData::getMapData()->HasMonster()) {
				if (GameData::getMapData()->getMonster()->getHP() == 0 || GameData::getMapData()->getMonster()->getWeak() == 0) {
					DownStairButton->setVisible(true);
					DownStairButton->setEnabled(true);
				}
				else {
					DownStairButton->setVisible(false);
					DownStairButton->setEnabled(false);
				}
			}
			else {
				DownStairButton->setVisible(true);
				DownStairButton->setEnabled(true);
			}
		}
		RightDoorImage->setOpacity(0);
		LeftDoorImage->setOpacity(0);
	}

	//캐릭터 애니메이션 및 초기모습 설정
	PlayerStand();
	if (GameData::getPlayer()->getDirect() == 1) //오른쪽 보고있을때
	{
		playerImage->setPosition(Point(visibleSize.width / 2 - 100, visibleSize.height / 2));
	}
	else {
		playerImage->setPosition(Point(visibleSize.width / 2 + 100, visibleSize.height / 2));
	}
	
	//몬스터가 있는지 없는지, 몬스터 애니메이션
	MonsterImage->stopAllActions();
	if (GameData::getMapData()->HasMonster()) {
		setMonsterImg();
		if (GameData::getInGameData()->getRoomNum() == 0) {
			MonsterImage->setPosition(Point(visibleSize.width / 2 - 80, visibleSize.height / 2 - 50));
			MonsterImage->setFlipX(true); //좌우반전
		}
		else {
			MonsterImage->setPosition(Point(visibleSize.width / 2 + 80, visibleSize.height / 2 - 50));
			MonsterImage->setFlipX(false);
		}
		MonsterImage->setScale(1.0f);
		MonsterImage->setOpacity(255);
		if (GameData::getMapData()->getMonster()->getHP() != 0) {
			if (GameData::getMapData()->getMonster()->getWeak() == 0)
				MonsterImage->runAction(RepeatForever::create(
					Sequence::create(
						SkewBy::create(0.5f, 6, 0),
						SkewBy::create(1, -12, 0),
						SkewBy::create(0.5f, 6, 0),
						nullptr)));
			else
				MonsterImage->runAction(RepeatForever::create(
					Sequence::create(
						ScaleTo::create(1, 1 * 1.1),
						ScaleTo::create(1, 1),
						nullptr)));
		}
	}
	else {
		MonsterImage->setScale(1.2f);
		if (GameData::getInGameData()->getRoomNum() == 0) {
			MonsterImage->setPosition(Point(visibleSize.width / 2 - 80, visibleSize.height / 2 - 80));
			MonsterImage->setFlipX(true); //좌우반전
		}
		else {
			MonsterImage->setPosition(Point(visibleSize.width / 2 + 80, visibleSize.height / 2 - 80));
			MonsterImage->setFlipX(false);
		}
		if (GameData::getMapData()->getType() == 3) {
			getChildByName<CCSprite*>("MonsterImage")->setTexture("gfx/monster/angel.png");
			MonsterImage->setOpacity(255);
		}
		else if (GameData::getMapData()->getType() == 4) {
			getChildByName<CCSprite*>("MonsterImage")->setTexture("gfx/monster/devil.png");
			MonsterImage->setOpacity(255);
		}
		else if (GameData::getMapData()->getType() == 5) {
			getChildByName<CCSprite*>("MonsterImage")->setTexture("gfx/monster/goldBox.png");
			MonsterImage->setOpacity(255);
		}
		else
			MonsterImage->setOpacity(0);
	}
	if(GameData::getPlayer()->getHP() <= 0) //게임오버 상황
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, GameOverScene::createScene()));
}

void GameScene::PlayerStand() //서있는 애니메이션 동작
{
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	//playerImage->getActionManager()->removeAllActions();
	playerImage->stopAllActions();
	if (GameData::getPlayer()->getDirect() == 1) { //오른쪽 보고있을때
		auto animation = CCAnimation::createWithSpriteFrames(playerRightStandF, 0.5f);
		auto animate = CCAnimate::create(animation);
		auto req = CCRepeatForever::create(animate);
		playerImage->runAction(req);
	}
	else {
		auto animation = CCAnimation::createWithSpriteFrames(playerLeftStandF, 0.5f);
		auto animate = CCAnimate::create(animation);
		auto req = CCRepeatForever::create(animate);
		playerImage->runAction(req);
	}
	
}

void GameScene::PlayerRun()
{
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	//playerImage->getActionManager()->removeAllActions();
	playerImage->stopAllActions();
	if (GameData::getPlayer()->getDirect() == 1) { //오른쪽 보고있을때
		auto animation = CCAnimation::createWithSpriteFrames(playerRightRunF, 0.25f);
		auto animate = CCAnimate::create(animation);
		auto req = CCRepeatForever::create(animate);
		playerImage->runAction(req);
	}
	else {
		auto animation = CCAnimation::createWithSpriteFrames(playerLeftRunF, 0.25f);
		auto animate = CCAnimate::create(animation);
		auto req = CCRepeatForever::create(animate);
		playerImage->runAction(req);
	}
}

void GameScene::ScreenFadeIn(float f)
{
	auto blackScreen = getChildByName<CCSprite*>("blackScreen");
	blackScreen->runAction(FadeIn::create(0.8f));
}

void GameScene::ScreenFadeOut(float f) //다시 페이드아웃할때 동작
{
	SceneLoad();
	auto blackScreen = getChildByName<CCSprite*>("blackScreen");
	blackScreen->runAction(FadeOut::create(0.8f));
	this->scheduleOnce(schedule_selector(GameScene::setCanClick), 0.9f);
	setText();
	setGageScale();
	log("floorNum = %d , roomNum = %d, roomType = %d monster = %d", GameData::getInGameData()->getFloorNum(), GameData::getInGameData()->getRoomNum(), GameData::getMapData()->getType(),(GameData::getMapData()->HasMonster()?0:1));
}

void GameScene::GoLeftDoor()
{
	auto LeftDoorImage = getChildByName<CCSprite*>("LeftDoorImage");
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	if (GameData::getInGameData()->getFloorNum() != GameData::MAX_FLOOR && GameData::getInGameData()->getFloorNum() != 1) {
		int r = GameData::getInGameData()->getRoomNum();
		if (r > 0) {
			canClick = false;
			GameData::getInGameData()->setRoonNum(--r);
			GameData::getPlayer()->setDirect(2); //방향 오른쪽
			PlayerRun();
			auto action = MoveTo::create(1.0f, Vec2(LeftDoorImage->getPositionX(), LeftDoorImage->getPositionY()-10));
			playerImage->runAction(action);
			this->scheduleOnce(schedule_selector(GameScene::GoNextScreen), 1.2f);
			GameData::getPlayer()->addHunger(-1);
		}
	}
}

void GameScene::GoRightDoor()
{
	auto RightDoorImage = getChildByName<CCSprite*>("RightDoorImage");
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	if (GameData::getInGameData()->getFloorNum() != GameData::MAX_FLOOR && GameData::getInGameData()->getFloorNum() != 1) {
		int r = GameData::getInGameData()->getRoomNum();
		if (r < 2) {
			canClick = false;
			GameData::getInGameData()->setRoonNum(++r);
			GameData::getInGameData()->getPlayer()->setDirect(1); //방향 왼쪽
			PlayerRun();
			playerImage->runAction(MoveTo::create(1.0f, Vec2(RightDoorImage->getPositionX(), RightDoorImage->getPositionY() - 10)));
			this->scheduleOnce(schedule_selector(GameScene::GoNextScreen), 1.2f);
			GameData::getPlayer()->addHunger(-1);

		}
	}
}

void GameScene::GoDownFloor()
{
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	if (GameData::getInGameData()->getFloorNum() > 1) {
		if (GameData::getInGameData()->getRoomNum() == 1) {
			canClick = false;
			PlayerRun();
			playerImage->runAction(MoveTo::create(1.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2)));
			this->scheduleOnce(schedule_selector(GameScene::GoNextScreen), 1.0f);
			GameData::getPlayer()->setDirect(1);
			GameData::getInGameData()->downTheFloor();
			GameData::getInGameData()->gameSetting();
			GameData::getPlayer()->addHunger(-1);
			DatabaseManager::getInstance()->saveAllData();
		}
	}
}

void GameScene::GoNextScreen(float f)
{
	auto getItemImage = getChildByName<CCSprite*>("getItemImage");
	PlayerStand();
	getItemImage->setOpacity(0);
	ScreenFadeIn(0.8f);
	this->scheduleOnce(schedule_selector(GameScene::ScreenFadeOut), 0.9f);
}

void GameScene::setText() //텍스트정보 수정
{
	auto Floor_label = getChildByName("statusImage")->getChildByName<CCSprite*>("floorBox")->getChildByName<Label*>("Floor_label");
	auto HP_label = getChildByName("statBox")->getChildByName<Label*>("HP_label");
	auto Hunger_label = getChildByName("statBox")->getChildByName<Label*>("Hunger_label");
	auto DA_label = getChildByName("statBox")->getChildByName<Label*>("DA_label");
	textString.str("");
	textString.clear();
	textString << GameData::getInGameData()->getFloorNum();
	Floor_label->setString(textString.str()+"F");
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getHP();
	HP_label->setString(textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getHunger();
	Hunger_label->setString(textString.str());
	textString.str("");
	textString.clear();
	if (GameData::getPlayer()->getDevil() > GameData::getPlayer()->getAngel())
		textString << GameData::getPlayer()->getDevil();
	else
		textString << GameData::getPlayer()->getAngel();
	DA_label->setString(textString.str());
}

void GameScene::setGageScale()
{
	auto HP_Gage = getChildByName("statBox")->getChildByName<CCSprite*>("HP_Gage");
	auto Hunger_Gage = getChildByName("statBox")->getChildByName<CCSprite*>("Hunger_Gage");
	auto Devil_Gage = getChildByName("statBox")->getChildByName<CCSprite*>("Devil_Gage");
	auto Angel_Gage = getChildByName("statBox")->getChildByName<CCSprite*>("Angel_Gage");
	HP_Gage->runAction(ScaleTo::create(0.5f, float(GameData::getPlayer()->getHP() / Player::MAX_HP), 1));
	Hunger_Gage->runAction(ScaleTo::create(0.5f, ((float)GameData::getPlayer()->getHunger() / Player::MAX_HUNGER), 1));
	Devil_Gage->runAction(ScaleTo::create(0.5f, (float(GameData::getPlayer()->getDevil() / 100.0f)), 1));
	Angel_Gage->runAction(ScaleTo::create(0.5f, (float(GameData::getPlayer()->getAngel() / 100.0f)), 1));
}

void GameScene::setMonsterImg()
{
	auto MonsterImage = getChildByName<CCSprite*>("MonsterImage");
	switch (GameData::getMapData()->getMonster()->getType()) {
	case 0:
		if(GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster1.png");
		else
			MonsterImage->setTexture("gfx/monster/monster1_dead.png");
		break;
	case 1:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster2.png");
		else
			MonsterImage->setTexture("gfx/monster/monster2_dead.png");
		break;
	case 2:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster3.png");
		else
			MonsterImage->setTexture("gfx/monster/monster3_dead.png");
		break;
	case 3:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster4.png");
		else
			MonsterImage->setTexture("gfx/monster/monster4_dead.png");
		break;
	case 4:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster5.png");
		else
			MonsterImage->setTexture("gfx/monster/monster5_dead.png");
		break;
	case 5:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster6.png");
		else
			MonsterImage->setTexture("gfx/monster/monster6_dead.png");
		break;
	case 9:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster10.png");
		else
			MonsterImage->setTexture("gfx/monster/monster10_dead.png");
		break;
	default:
		if (GameData::getMapData()->getMonster()->getHP() > 0)
			MonsterImage->setTexture("gfx/monster/monster1.png");
		else
			MonsterImage->setTexture("gfx/monster/monster1_dead.png");
		break;
	}
}

void GameScene::itemGetAnimation(CCNode *node)
{
	auto playerImage = getChildByName<CCSprite*>("playerImage");
	auto getItemImage = getChildByName<CCSprite*>("getItemImage");
	//아이템 이미지 등록
	if (itemAniNum > 3 || itemTypeList[itemAniNum] >= 100) { //애니메이션 종료
		GameData::getMapData()->clearItemList();
		canClick = true;
		for (int i = 0; i < 4; i++)
			itemTypeList[i] = 100;
		itemAniNum = 0;
		DatabaseManager::getInstance()->saveItemList();
	}
	else {
		getItemImage->setTexture(GameData::getInGameData()->getItemImage(itemTypeList[itemAniNum])->getTexture());
		getItemImage->setPosition(Point(playerImage->getPositionX(), playerImage->getPositionY() + 48)); //이미지 위치이동
		getItemImage->setOpacity(255);
		auto fadeOut = FadeOut::create(0.35f);
		getItemImage->runAction(fadeOut);
		auto action = MoveBy::create(0.35f, Vec2(0, 36));
		getItemImage->runAction(action);//getItemImage 에 투명도변화, 위로 올라가는 효과 애니메이션
		itemAniNum++;
		CCDelayTime * delayAction = CCDelayTime::create(0.4f);
		CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::itemGetAnimation));
		this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));
		if (GameData::getGameData()->getEffect() > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/pharmEffect.mp3");
		}
	}
}
void GameScene::getItems()
{
	int i = 0;
	GameData::getMapData()->setItemList();
	while (i < 4 && GameData::getMapData()->getItemListType(i) != 100) {
		GameData::getPlayer()->addItem(GameData::getMapData()->getItemListType(i));
		itemTypeList[i] = GameData::getMapData()->getItemListType(i);
		log("%d %d",i, GameData::getMapData()->getItemListType(i));
		i++;
	}
	if (i > 0)
		itemGetAnimation(NULL);//애니메이션 작동
	else
		canClick = true;
}

void GameScene::addMenuLayer()
{
	auto menuLayer = Layer::create();
	menuLayer->setName("menuLayer");
	menuLayer->setPosition(Point::ZERO);
	auto menuBG = CCSprite::create("gfx/object/gameMenuBG.png");
	menuBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto menuPane = CCSprite::create("gfx/object/battlePane.png");
	menuPane->setScale(0.85f);
	menuPane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto BackButton = MenuItemImage::create(
		"gfx/icon/cancelButton.png",
		"gfx/icon/cancelButton_clicked.png",
		CC_CALLBACK_1(GameScene::BackClicked, this));
	BackButton->setName("BackButton");
	BackButton->setPosition(Point(410, 490));
	auto BGMButton = MenuItemImage::create(
		"gfx/icon/audio_on.png",
		"gfx/icon/audio_on.png",
		CC_CALLBACK_1(GameScene::BGMClicked, this));
	BGMButton->setName("BGMButton");
	BGMButton->setScale(0.8f);
	BGMButton->setPosition(Point(visibleSize.width / 2 - 120, visibleSize.height / 2));
	auto BGMLabel = Label::createWithTTF("BGM", "fonts/NanumPen.ttf", 24, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	BGMLabel->setPosition(Point(visibleSize.width / 2 - 120, visibleSize.height / 2 + 70));
	BGMLabel->setColor(Color3B::BLACK);
	
	auto EffectButton = MenuItemImage::create(
		"gfx/icon/audio_on.png",
		"gfx/icon/audio_on.png",
		CC_CALLBACK_1(GameScene::EffectClicked, this));
	EffectButton->setName("EffectButton");
	EffectButton->setScale(0.8f);
	EffectButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto EffectLabel = Label::createWithTTF("Effect", "fonts/NanumPen.ttf", 24, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	EffectLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 70));
	EffectLabel->setColor(Color3B::BLACK);
	auto HomeButton = MenuItemImage::create(
		"gfx/icon/home_icon.png",
		"gfx/icon/home_icon_clicked.png",
		CC_CALLBACK_1(GameScene::HomeClicked, this));
	HomeButton->setName("HomeButton");
	HomeButton->setScale(0.8f);
	HomeButton->setPosition(Point(visibleSize.width / 2 + 120, visibleSize.height / 2));
	if (GameData::getGameData()->getBGM() == 0) {
		BGMButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		BGMButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
	}
	if (GameData::getGameData()->getEffect() == 0) {
		EffectButton->setNormalImage(CCSprite::create("gfx/icon/audio_off.png"));
		EffectButton->setSelectedImage(CCSprite::create("gfx/icon/audio_off.png"));
	}

	auto menuMenu = Menu::create(BackButton, BGMButton, EffectButton, HomeButton, NULL);
	menuMenu->setName("menuMenu");
	menuMenu->setPosition(Point(0, 0));

	menuLayer->addChild(menuBG, 0);
	menuLayer->addChild(menuPane, 1);
	menuLayer->addChild(menuMenu, 2);
	menuLayer->addChild(BGMLabel, 3);
	menuLayer->addChild(EffectLabel, 4);

	addChild(menuLayer, 7);
	setButtonEnable(false);
}

void GameScene::deleteMenuLayer()
{
	removeChildByName("menuLayer");
	setButtonEnable(true);
}

void GameScene::setButtonEnable(bool b) //false: 게임버튼비활성화, true: 게임버튼 활성화
{
	auto LeftClickButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("LeftClickButton");
	auto RightClickButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("RightClickButton");
	auto DownStairButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("DownStairButton");
	auto PharmButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("PharmButton");
	auto BattleButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("BattleButton");
	auto MenuButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("MenuButton");
	auto ItemButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("ItemButton");
	if (b) {
		SceneLoad();
		MenuButton->setEnabled(true);
		ItemButton->setEnabled(true);
	}
	else {
		LeftClickButton->setEnabled(false);
		RightClickButton->setEnabled(false);
		DownStairButton->setEnabled(false);
		PharmButton->setEnabled(false);
		BattleButton->setEnabled(false);
		MenuButton->setEnabled(false);
		ItemButton->setEnabled(false);
	}
}

void GameScene::createCommuPane()
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
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		case 2:
			GameData::getTextManager()->createText("tutorial1.txt");
			break;
		case 4:
			GameData::getTextManager()->createText("tutorial2.txt");
			break;
		case 6:
			if(cancelNum == 0)
				GameData::getTextManager()->createText("tutorial3.txt");
			else if (cancelNum == 1)
				GameData::getTextManager()->createText("tutorial5.txt");
			else if(cancelNum == 6)
				GameData::getTextManager()->createText("tutorial7.txt");
			else
				GameData::getTextManager()->createText("tutorial6.txt");
			break;
		case 8:
			if (cancelNum <= 5)
				GameData::getTextManager()->createText("tutorial8.txt");
			else
				GameData::getTextManager()->createText("tutorial9.txt");
			break;
		default:
			GameData::getTextManager()->createText("tutorial0.txt");
			break;
		}
	}
	auto commuLayer = Layer::create();
	commuLayer->setName("commuLayer");
	commuLayer->setPosition(Point::ZERO);
	auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
	backImg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto nextButton = MenuItemImage::create(
		"gfx/icon/nextText.png",
		"gfx/icon/nextText_clicked.png",
		CC_CALLBACK_1(GameScene::NextTextClicked, this));
	nextButton->setName("nextButton");
	nextButton->setPosition(Point(420, 50));
	auto previousButton = MenuItemImage::create(
		"gfx/icon/previousText.png",
		"gfx/icon/previousText_clicked.png",
		CC_CALLBACK_1(GameScene::PreviousTextClicked, this));
	previousButton->setName("previousButton");
	previousButton->setPosition(Point(60, 50));
	previousButton->setVisible(false);
	previousButton->setEnabled(false);
	auto skipButton = MenuItemImage::create(
		"gfx/icon/skip_icon.png",
		"gfx/icon/skip_icon_clicked.png",
		CC_CALLBACK_1(GameScene::SkipClicked, this));
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
	contextPane->setPosition(Point(visibleSize.width / 2, 120));
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

void GameScene::setCommuPane()
{
	auto contextPane = getChildByName("commuLayer")->getChildByName<CCSprite*>("contextPane");
	auto namePane = getChildByName("commuLayer")->getChildByName<CCSprite*>("namePane");
	auto charImg = getChildByName("commuLayer")->getChildByName<CCSprite*>("charImg");
	auto contentLabel = getChildByName("commuLayer")->getChildByName("contextPane")->getChildByName<Label*>("contentLabel");
	auto nameLabel = getChildByName("commuLayer")->getChildByName("namePane")->getChildByName<Label*>("nameLabel");

	contextPane->stopAllActions();
	namePane->stopAllActions();
	charImg->stopAllActions();
	if(charImg->getColor() == Color3B::BLACK)
		charImg->setColor(Color3B::WHITE);

	switch (GameData::getTextManager()->getTextNode()->getImg()) {
	case 0:
		if(GameData::getTextManager()->getTextNode()->getEffect() == 0) //일반표정
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
	contextPane->setPosition(Point(visibleSize.width / 2, 100));
	contextPane->runAction(Spawn::create(
		FadeIn::create(0.3f),
		MoveTo::create(0.3f, Vec2(visibleSize.width / 2, 120)),
		nullptr));
	
}

void GameScene::deleteCommuPane()
{
	removeChildByName("commuLayer");
	setButtonEnable(true);
}

void GameScene::createSelectPane(int n)
{
	if (n == 0) {
		std::string tempText[3];
		textString.str("");
		textString.clear();
		//텍스트 불러오기
		GameData::getTextManager()->createText("tutorial4.txt");
		for (int i = 0; i < 3; i++)
			tempText[i] = GameData::getTextManager()->getTextList()->pop();
		auto selectLayer = Layer::create();
		selectLayer->setName("selectLayer");
		selectLayer->setPosition(Point::ZERO);
		auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
		backImg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto menuPane = CCSprite::create("gfx/object/selectPane.png");
		menuPane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto menu_label = Label::createWithTTF("hi", "fonts/HoonWhitecatR.ttf", 32, Size(0, 0),
			TextHAlignment::CENTER, TextVAlignment::CENTER);
		menu_label->setPosition(Point(200, 150));
		menu_label->setColor(Color3B::BLACK);
		textString << tempText[0];
		menu_label->setString(textString.str());
		auto equipBox = CCSprite::create("gfx/object/equipBottom.png");
		equipBox->setPosition(Point(120, 230));
		auto knifeImage = CCSprite::create("gfx/item/macgyver.png");
		knifeImage->setPosition(Point(48, 48));
		equipBox->addChild(knifeImage);
		auto okButton = MenuItemImage::create(
			"gfx/icon/selectButton.png",
			"gfx/icon/selectButton_clicked.png",
			CC_CALLBACK_1(GameScene::okClicked, this));
		okButton->setPosition(Vec2(120, 80));
		auto ok_label = Label::createWithTTF("hi", "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
			TextHAlignment::CENTER, TextVAlignment::CENTER);
		ok_label->setPosition(Point(60, 40));
		ok_label->setColor(Color3B::BLACK);
		textString.str("");
		textString << tempText[1];
		ok_label->setString(textString.str());
		okButton->addChild(ok_label);
		auto cancelButton = MenuItemImage::create(
			"gfx/icon/selectButton.png",
			"gfx/icon/selectButton_clicked.png",
			CC_CALLBACK_1(GameScene::cancelClicked, this));
		cancelButton->setPosition(Vec2(280, 80));
		auto cancel_label = Label::createWithTTF("hi", "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
			TextHAlignment::CENTER, TextVAlignment::CENTER);
		cancel_label->setPosition(Point(60, 40));
		cancel_label->setColor(Color3B::BLACK);
		textString.str("");
		textString << tempText[2];
		cancel_label->setString(textString.str());
		cancelButton->addChild(cancel_label);
		auto menu = Menu::create(okButton, cancelButton, NULL);
		menu->setPosition(Point::ZERO);
		menuPane->addChild(equipBox);
		menuPane->addChild(menu_label);
		menuPane->addChild(menu);
		selectLayer->addChild(backImg, 0);
		selectLayer->addChild(menuPane, 1);
		addChild(selectLayer, 8);
	}
	else if (n == 1) {
		std::string tempText[3];
		textString.str("");
		textString.clear();
		//텍스트 불러오기
		GameData::getTextManager()->createText("tutorial10.txt");
		for (int i = 0; i < 3; i++)
			tempText[i] = GameData::getTextManager()->getTextList()->pop();
		auto selectLayer = Layer::create();
		selectLayer->setName("selectLayer");
		selectLayer->setPosition(Point::ZERO);
		auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
		backImg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto menuPane = CCSprite::create("gfx/object/selectPane.png");
		menuPane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		auto menu_label = Label::createWithTTF("hi", "fonts/HoonWhitecatR.ttf", 32, Size(0, 0),
			TextHAlignment::CENTER, TextVAlignment::CENTER);
		menu_label->setPosition(Point(200, 150));
		menu_label->setColor(Color3B::BLACK);
		if(cancelNum > 5)
			textString << tempText[1];
		else
			textString << tempText[0];
		menu_label->setString(textString.str());
		auto equipBox = CCSprite::create("gfx/object/equipBottom.png");
		equipBox->setPosition(Point(120, 230));
		CCSprite* Image;
		if (cancelNum > 5)
			Image = CCSprite::create("gfx/item/rabbit_doll.png");
		else
			Image = CCSprite::create("gfx/item/macgyver.png");
		Image->setPosition(Point(48, 48));
		equipBox->addChild(Image);
		auto okButton = MenuItemImage::create(
			"gfx/icon/selectButton.png",
			"gfx/icon/selectButton_clicked.png",
			CC_CALLBACK_1(GameScene::okClicked, this));
		okButton->setPosition(Vec2(200, 80));
		auto ok_label = Label::createWithTTF("hi", "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
			TextHAlignment::CENTER, TextVAlignment::CENTER);
		ok_label->setPosition(Point(60, 40));
		ok_label->setColor(Color3B::BLACK);
		textString.str("");
		textString << tempText[2];
		ok_label->setString(textString.str());
		okButton->addChild(ok_label);
		auto menu = Menu::create(okButton, NULL);
		menu->setPosition(Point::ZERO);
		menuPane->addChild(equipBox);
		menuPane->addChild(menu_label);
		menuPane->addChild(menu);
		selectLayer->addChild(backImg, 0);
		selectLayer->addChild(menuPane, 1);
		addChild(selectLayer, 8);
	}
}

void GameScene::tutorialSetting(CCNode *node)
{
	CCSprite* img = NULL;
	auto BattleButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("BattleButton");
	auto ItemButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("ItemButton");
	auto MenuButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("MenuButton");
	CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::tutorialSetting));
	switch (tutorialCase) {
	case 0:
		setButtonEnable(false);
		img = CCSprite::create("gfx/object/tutorialBGDark.png");
		img->setName("dark");
		img->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		addChild(img, 7);
		createCommuPane();
		break;
	case 1:
		setButtonEnable(false);
		img = getChildByName<CCSprite*>("dark");
		img->runAction(FadeOut::create(2.0f));
		tutorialCase++;
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.5f), callFunc));
		break;
	case 2:
		removeChildByName("dark");
		createCommuPane();
		break;
	case 3:
		setButtonEnable(false);
		img = getChildByName<CCSprite*>("statBox");
		img->runAction(Sequence::create(
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			nullptr));
		tutorialCase++;
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.5f), callFunc));
		break;
	case 4:
		createCommuPane();
		break;
	case 5:
		setButtonEnable(false);
		BattleButton->runAction(Sequence::create(
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			nullptr));
		ItemButton->runAction(Sequence::create(
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			nullptr));
		MenuButton->runAction(Sequence::create(
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			ScaleTo::create(0.4f, 1.2f),
			ScaleTo::create(0.4f, 1.0f),
			nullptr));
		tutorialCase++;
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.5f), callFunc));
		break;
	case 6:
		createCommuPane();
		break;
	case 7:
		//칼 받는다 안받는다 선택
		setButtonEnable(false);
		createSelectPane(0);
		break;
	case 8:
		createCommuPane();
		break;
	case 9:
		setButtonEnable(false);
		createSelectPane(1);
		break;
	case 10:
		MenuButton->setEnabled(false);
		ItemButton->setEnabled(false);
		BattleButton->runAction(RepeatForever::create(Sequence::create(
			ScaleTo::create(0.4f, 1.1f),
			ScaleTo::create(0.4f, 1.0f),
			nullptr)));
		break;
	}
}

void GameScene::BattleClicked(cocos2d::Ref * pSender)
{
	log("BattleButton clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		if (GameData::getMapData()->HasMonster() && GameData::getMapData()->getMonster()->getHP() > 0 && GameData::getMapData()->getMonster()->getWeak() > 0) {
			auto BattleScene = CCTransitionFadeBL::create(0.5f, BattleScene::createScene());
			Director::getInstance()->replaceScene(BattleScene);
		}
	}
}

void GameScene::ItemClicked(cocos2d::Ref * pSender)
{
	log("ItemButton clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		auto ItemScene = CCTransitionFadeDown::create(0.5f, ItemScene::createScene());
		Director::getInstance()->replaceScene(ItemScene);
	}
}

void GameScene::LeftClicked(cocos2d::Ref * pSender)
{
	log("left clicked! & %s",(canClick == true ? "true" : "false"));
	if (canClick==true) {
		GoLeftDoor();
	}
}

void GameScene::RightClicked(cocos2d::Ref * pSender)
{
	log("right clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		GoRightDoor();
	}
}

void GameScene::NextClicked(cocos2d::Ref * pSender)
{
	log("next button clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		if(!GameData::getMapData()->HasMonster())
			GoDownFloor();
		else {
			if (GameData::getMapData()->getMonster()->getHP() == 0 || GameData::getMapData()->getMonster()->getWeak() == 0)
				GoDownFloor();
		}
	}
}

void GameScene::PharmingClicked(cocos2d::Ref * pSender) //아이템 파밍
{
	auto PharmButton = getChildByName<Menu*>("pMenu")->getChildByName<MenuItemImage*>("PharmButton");
	log("Parming button clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		if (GameData::getMapData()->getIsItemParm()) {
			if (GameData::getMapData()->HasMonster()) { //몬스터가 있다
				if (GameData::getMapData()->getMonster()->getHP() == 0) { //근데 죽었다
					//해당몬스터 전용템과 일반템 0~2개
					getItems();
					canClick = false;
					PharmButton->setVisible(false);
					PharmButton->setVisible(false);
				}
				else if (GameData::getMapData()->getMonster()->getWeak() == 0) { //근데 교화시켰다
					//해당몬스터 회피템과 일반템 0~2개
					getItems();
					canClick = false;
					PharmButton->setVisible(false);
					PharmButton->setVisible(false);
				}
			}
			else { //몬스터가 없다
				//일반템 0~4개
				getItems();
				canClick = false;
				PharmButton->setVisible(false);
				PharmButton->setVisible(false);
			}
		}
	}
}

void GameScene::EventClicked(cocos2d::Ref * pSender) //이벤트씬 돌입
{
	log("Event button clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		if(GameData::getInGameData()->getFloorNum() == 1)
			Director::getInstance()->replaceScene(CCTransitionFadeBL::create(0.5f, EndingScene::createScene()));
		else
			Director::getInstance()->replaceScene(CCTransitionFadeBL::create(0.5f, EventScene::createScene()));
	}
}

void GameScene::MenuClicked(cocos2d::Ref * pSender) //메뉴버튼 클릭(레이어 생성)
{
	log("Menu button clicked! & %s", (canClick == true ? "true" : "false"));
	if (canClick == true) {
		addMenuLayer();
	}
}

void GameScene::BackClicked(cocos2d::Ref * pSender) //메뉴에서 뒤로가기
{
	log("Back button clicked!");
	deleteMenuLayer();
}

void GameScene::BGMClicked(cocos2d::Ref * pSender) //메뉴에서 셋팅버튼
{
	auto BGMButton = getChildByName("menuLayer")->getChildByName("menuMenu")->getChildByName<MenuItemImage*>("BGMButton");
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

void GameScene::EffectClicked(cocos2d::Ref * pSender) //메뉴에서 도움말버튼
{
	auto EffectButton = getChildByName("menuLayer")->getChildByName("menuMenu")->getChildByName<MenuItemImage*>("EffectButton");
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

void GameScene::HomeClicked(cocos2d::Ref * pSender) //메뉴에서 홈버튼
{
	log("Home button clicked!");
	DatabaseManager::getInstance()->saveAllData();
	auto mainScene = CCTransitionFade::create(1.2f, MainScene::createScene());
	Director::getInstance()->replaceScene(mainScene);
}

void GameScene::NextTextClicked(cocos2d::Ref * pSender)
{
	log("next button clicked!");
	if (GameData::getInGameData()->getCommuNum() == GameData::getInGameData()->getTextManager()->getTextList()->lastNodeNum()) {
		GameData::getInGameData()->setCommuCase(0);
		GameData::getInGameData()->setCommuNum(0);
		deleteCommuPane();
		if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < GameScene::MAX_TUTORIAL) {
			tutorialCase++;
			tutorialSetting(NULL);
		}
	}
	else {
		GameData::getInGameData()->nextText();
		if (GameData::getGameData()->getEffect() > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/page_turn.mp3");
		}
		if (GameData::getInGameData()->getCommuNum() > 0) {
			auto previousButton = getChildByName("commuLayer")->getChildByName("commuMenu")->getChildByName<MenuItemImage*>("previousButton");
			previousButton->setVisible(true);
			previousButton->setEnabled(true);
		}
		setCommuPane();
	}
}

void GameScene::PreviousTextClicked(cocos2d::Ref * pSender)
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

void GameScene::SkipClicked(cocos2d::Ref * pSender)
{
	log("skip button clicked!");
	GameData::getInGameData()->setCommuCase(0);
	GameData::getInGameData()->setCommuNum(0);
	deleteCommuPane();
	if (GameData::getInGameData()->getFloorNum() == 50 && tutorialCase < GameScene::MAX_TUTORIAL) {
		tutorialCase++;
		tutorialSetting(NULL);
	}
}

void GameScene::okClicked(cocos2d::Ref * pSender)
{
	log("ok button clicked!");
	if (tutorialCase == 7)
		GameData::getPlayer()->addEquipItem(25);
	else if (tutorialCase == 9) {
		setButtonEnable(true);
	}
	tutorialCase++;
	removeChildByName("selectLayer");
	tutorialSetting(NULL);
}

void GameScene::cancelClicked(cocos2d::Ref * pSender)
{
	log("cancel button clicked!");
	if (cancelNum > 5) {
		tutorialCase++;
		GameData::getPlayer()->addEquipItem(26);
	}
	else {
		tutorialCase--;
		cancelNum++;
	}
	removeChildByName("selectLayer");
	tutorialSetting(NULL);
}
