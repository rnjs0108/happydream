#include "EventScene.h"
#include "SimpleAudioEngine.h"
#include "DatabaseManager.h"
#include "GameData.h"
#include "GameScene.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;

Scene* EventScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EventScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool EventScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	choiceNum = 0;
	caseNum = 0;

	auto building = CCSprite::create("gfx/backGround/blackScreen.png");
	building->setName("building");
	building->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto roomBG = GameData::getGameData()->setRoomBGImage();
	roomBG->setName("roomBG");
	roomBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto doorImage = CCSprite::create("gfx/object/door_l.png");
	doorImage->setName("doorImage");
	auto StatueImage = setStatueImage();
	StatueImage->setName("StatueImage");
	StatueImage->setAnchorPoint(Vec2(0.5, 0));
	StatueImage->setScale(1.2f);
	if (GameData::getInGameData()->getRoomNum() == 0) { //좌측방
		StatueImage->setPosition(Point(100, 40));
		StatueImage->setFlipX(true); //좌우반전
		doorImage->setPosition(Point(300, 140));
		doorImage->setTexture("gfx/object/door_r.png");
	}
	else {
		StatueImage->setPosition(Point(260, 40));
		StatueImage->setFlipX(false);
		doorImage->setPosition(Point(60, 140));
	}
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
	}
	auto playerImage = CCSprite::createWithSpriteFrameName("player00.png");
	playerImage->setName("playerImage");
	if (GameData::getPlayer()->getDirect() == 1) //오른쪽 보고있을때
	{
		playerImage->setPosition(Point(80, 100));
	}
	else {
		playerImage->setPosition(Point(280, 100));
	}

	roomBG->addChild(doorImage, 0);
	roomBG->addChild(StatueImage, 1);
	roomBG->addChild(playerImage, 2);
	roomBG->setScale(1.33f);

	addChild(building, 0);
	addChild(roomBG, 1);

	PlayerStand();
	createCommuPane();
	if(GameData::getInGameData()->getMapData()->getType()==3)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/AngelBGM.mp3", true);
	else if (GameData::getInGameData()->getMapData()->getType() == 4)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/DevilBGM.mp3", true);
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/AngelBGM.mp3", true);
	if (GameData::getGameData()->getBGM() == 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	return true;
}

void EventScene::PlayerStand() //서있는 애니메이션 동작
{
	auto playerImage = getChildByName("roomBG")->getChildByName<CCSprite*>("playerImage");
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

CCSprite * EventScene::setStatueImage()
{
	CCSprite* statuImage = CCSprite::create("gfx/monster/monster10.png");
	int i = GameData::getInGameData()->getMapData()->getType();
	switch (i) {
	case 3:
		statuImage->setTexture("gfx/monster/angel.png");
		break;
	case 4:
		statuImage->setTexture("gfx/monster/devil.png");
		break;
	case 5:
		statuImage->setTexture("gfx/monster/goldBox.png");
		break;
	}
	return statuImage;
}

int EventScene::setSituation()
{
	int result = 0;
	if (GameData::getMapData()->getType() == 5)
		result = 6;
	else {
		int randomNum = rand() % 3;
		result = randomNum + (GameData::getMapData()->getType() - 3)*3;
	}
	return result;
}

void EventScene::createCommuPane()
{
	if (choiceNum == 0) {
		switch (GameData::getMapData()->getType()) {
		case 3: //천사방
			GameData::getTextManager()->createText("angelIntro.txt");
			break;
		case 4: //악마방
			GameData::getTextManager()->createText("devilIntro.txt");
			break;
		case 5: //상자방
			GameData::getTextManager()->createText("boxIntro.txt");
			break;
		default:
			break;
		}
	}
	else if(choiceNum == 1) {
		caseNum = setSituation();
		switch (caseNum) {
		case 0: //축복 (천사)
			GameData::getTextManager()->createText("angel_bless.txt");
			break;
		case 1: //거래
			GameData::getTextManager()->createText("angel_deal.txt");
			break;
		case 2: //평가
			GameData::getTextManager()->createText("angel_eval.txt");
			break;
		case 3: //축복 (악마)
			GameData::getTextManager()->createText("devil_bless.txt");
			break;
		case 4: //거래
			GameData::getTextManager()->createText("devil_deal.txt");
			break;
		case 5: //평가
			GameData::getTextManager()->createText("devil_eval.txt");
			break;
		case 6: //상자
			GameData::getTextManager()->createText("box_open.txt");
			break;
		default:
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
		CC_CALLBACK_1(EventScene::NextTextClicked, this));
	nextButton->setName("nextButton");
	nextButton->setPosition(Point(420, 50));
	auto previousButton = MenuItemImage::create(
		"gfx/icon/previousText.png",
		"gfx/icon/previousText_clicked.png",
		CC_CALLBACK_1(EventScene::PreviousTextClicked, this));
	previousButton->setName("previousButton");
	previousButton->setPosition(Point(60, 50));
	previousButton->setVisible(false);
	previousButton->setEnabled(false);
	auto skipButton = MenuItemImage::create(
		"gfx/icon/skip_icon.png",
		"gfx/icon/skip_icon_clicked.png",
		CC_CALLBACK_1(EventScene::SkipClicked, this));
	skipButton->setName("skipButton");
	skipButton->setPosition(Point(400, 740));
	auto contentLabel = Label::createWithTTF("내용", "fonts/THE_Oegyeinseolmyeongseo.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	contentLabel->setName("contentLabel");
	contentLabel->setPosition(Point(230, 140));
	contentLabel->setColor(Color3B::BLACK);
	auto nameLabel = Label::createWithTTF("내용", "fonts/THE_Ppikkeutppikkeut.ttf", 32, Size(0, 0),
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

	addChild(commuLayer, 5);
	backImg->setOpacity(0);
	backImg->runAction(FadeIn::create(0.5f));
	setCommuPane();
}

void EventScene::setCommuPane()
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
	case 5:
		charImg->setTexture("gfx/player/goldBox.png");
		break;
	}

	if (GameData::getTextManager()->getTextNum() % 2 == (GameData::getInGameData()->getRoomNum() / 2)) { //동상 먼저 대화
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

void EventScene::deleteCommuPane()
{
	removeChildByName("commuLayer");
}

void EventScene::createChoicePane()
{
	std::string tempText[5];
	std::ostringstream textString;
	textString.str("");
	textString.clear();
	//텍스트 불러오기
	if (choiceNum == 0)
		GameData::getTextManager()->createText("eventText.txt");
	else if (choiceNum == 1) {
		if(caseNum == 6)
			GameData::getTextManager()->createText("eventText_box.txt");
		else {
			if(caseNum % 3 == 0) //축복
				GameData::getTextManager()->createText("eventText_bless.txt");
			else if (caseNum % 3 == 1) //거래
				GameData::getTextManager()->createText("eventText_deal.txt");
			else //평가
				GameData::getTextManager()->createText("eventText_eval.txt");
		}
	}
	for (int i = 0; i < 5; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();
	auto choiceLayer = Layer::create();
	choiceLayer->setName("choiceLayer");
	choiceLayer->setPosition(Point::ZERO);
	auto backImg = CCSprite::create("gfx/object/mainBGDark.png");
	backImg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	auto okButton = MenuItemImage::create(
		"gfx/icon/selectButton.png",
		"gfx/icon/selectButton_clicked.png",
		CC_CALLBACK_1(EventScene::okClicked, this));
	okButton->setName("okButton");
	okButton->setPosition(Point(120, 70));
	auto ok_label = Label::createWithTTF("hi", "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	ok_label->setName("ok_label");
	ok_label->setPosition(Point(60, 40));
	ok_label->setColor(Color3B::BLACK);
	textString.str("");
	textString << tempText[3];
	ok_label->setString(textString.str());
	okButton->addChild(ok_label);
	auto cancelButton = MenuItemImage::create(
		"gfx/icon/selectButton.png",
		"gfx/icon/selectButton_clicked.png",
		CC_CALLBACK_1(EventScene::cancelClicked, this));
	cancelButton->setName("cancelButton");
	cancelButton->setPosition(Point(350, 70));
	auto cancel_label = Label::createWithTTF("hi", "fonts/THE_Oegyeinseolmyeongseo.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	cancel_label->setPosition(Point(60, 40));
	cancel_label->setColor(Color3B::BLACK);
	textString.str("");
	textString << tempText[4];
	cancel_label->setString(textString.str());
	cancelButton->addChild(cancel_label);
	auto contentLabel = Label::createWithTTF("내용", "fonts/THE_Oegyeinseolmyeongseo.ttf", 32, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	contentLabel->setName("contentLabel");
	contentLabel->setPosition(Point(230, 170));
	contentLabel->setColor(Color3B::BLACK);
	textString.str("");
	textString << tempText[GameData::getMapData()->getType()-3]; //상황에 맞는 텍스트
	contentLabel->setString(textString.str());

	auto commuMenu = Menu::create(okButton, cancelButton, NULL);
	commuMenu->setName("commuMenu");
	commuMenu->setPosition(Point::ZERO);

	auto contextPane = CCSprite::create("gfx/object/commuPane.png");
	contextPane->setName("contextPane");
	contextPane->setPosition(Point(visibleSize.width / 2, 120));
	contextPane->addChild(contentLabel, 0);
	contextPane->addChild(commuMenu, 1);

	choiceLayer->addChild(backImg, 0);
	choiceLayer->addChild(contextPane, 1);

	addChild(choiceLayer, 4);
	backImg->setOpacity(255);
	backImg->runAction(FadeOut::create(1.0f));
}

void EventScene::setChoicePane(CCNode *node) //결과창
{
	auto okButton = getChildByName("choiceLayer")->getChildByName("contextPane")->getChildByName("commuMenu")->getChildByName<MenuItemImage*>("okButton");
	auto cancelButton = getChildByName("choiceLayer")->getChildByName("contextPane")->getChildByName("commuMenu")->getChildByName<MenuItemImage*>("cancelButton");
	auto contentLabel = getChildByName("choiceLayer")->getChildByName("contextPane")->getChildByName<Label*>("contentLabel");
	runEvent();

	cancelButton->setVisible(false);
	cancelButton->setEnabled(false);
	okButton->setPosition(Point(230, 70));
	okButton->getChildByName<Label*>("ok_label")->setString("확인");
}

void EventScene::runEvent() //event 실행 알고리즘
{
	auto contentLabel = getChildByName("choiceLayer")->getChildByName("contextPane")->getChildByName<Label*>("contentLabel");
	CCSprite* itemImage;
	std::string tempText[25];
	std::ostringstream textString;
	textString.str("");
	textString.clear();
	//텍스트 불러오기
	GameData::getTextManager()->createText("eventText_result.txt");
	for (int i = 0; i < 25; i++)
		tempText[i] = GameData::getTextManager()->getTextList()->pop();

	if (GameData::getMapData()->getType() == 3) { //천사방
		if (caseNum % 3 == 0){ //축복(능력치증가)
			textString << tempText[0];
			if (GameData::getPlayer()->getDevil() >= 0 && GameData::getPlayer()->getDevil() < 50) { //소폭 상승
				int randStatus = rand() % 6;
				switch (randStatus) {
				case 0: //공격력
					textString << tempText[7];
					textString << 2;
					textString << tempText[14];
					GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() + 2);
					break;
				case 1: //방어력
					textString << tempText[8];
					textString << 1;
					textString << tempText[14];
					GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() + 1);
					break;
				case 2: //명중률
					textString << tempText[9];
					textString << 3;
					textString << tempText[14];
					GameData::getPlayer()->addHit(3);
					break;
				case 3: //회피율
					textString << tempText[10];
					textString << 3;
					textString << tempText[14];
					GameData::getPlayer()->addEva(3);
					break;
				case 4: //체력회복
					textString << tempText[11];
					textString << 4;
					textString << tempText[16];
					GameData::getPlayer()->addHP(4);
					break;
				case 5: //배고픔회복
					textString << tempText[12];
					textString << 4;
					textString << tempText[16];
					GameData::getPlayer()->addHunger(4);
					break;
				}
			}
			else if (GameData::getPlayer()->getDevil() >= 50) { //대폭 상승
				int randStatus = rand() % 6;
				switch (randStatus) {
				case 0: //공격력
					textString << tempText[7];
					textString << 4;
					textString << tempText[14];
					GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() + 4);
					break;
				case 1: //방어력
					textString << tempText[8];
					textString << 2;
					textString << tempText[14];
					GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() + 2);
					break;
				case 2: //명중률
					textString << tempText[9];
					textString << 5;
					textString << tempText[14];
					GameData::getPlayer()->addHit(5);
					break;
				case 3: //회피율
					textString << tempText[10];
					textString << 5;
					textString << tempText[14];
					GameData::getPlayer()->addEva(5);
					break;
				case 4: //체력회복
					textString << tempText[11];
					textString << 8;
					textString << tempText[16];
					GameData::getPlayer()->addHP(8);
					break;
				case 5: //배고픔회복
					textString << tempText[12];
					textString << 8;
					textString << tempText[16];
					GameData::getPlayer()->addHunger(8);
					break;
				}
			}
			else { //선 게이지가 높을때(체력소모)
				int randStatus = rand() % 5 + GameData::getInGameData()->getLevel();
				textString << tempText[20];
				if (randStatus == 0)
					textString << tempText[22];
				else {
					textString << tempText[11];
					textString << randStatus;
					textString << tempText[17];
					GameData::getPlayer()->addHP(-randStatus);
				}
			}
		}
		else if (caseNum % 3 == 1) { //거래
			textString << "천사와 거래를 할 수 없다.";
		}
		else { //평가(올스텟 소폭)(대화게이지 감소)
			textString << tempText[2];
			if (GameData::getPlayer()->getDevil() >= 0 && GameData::getPlayer()->getDevil() < 50) { //소폭 상승
				textString << tempText[23];
				textString << 1;
				textString << tempText[14];
				GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() + 1);
				GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() + 1);
				GameData::getPlayer()->addHit(1);
				GameData::getPlayer()->addEva(1);
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() - 2);
			}
			else if (GameData::getPlayer()->getDevil() >= 50) { //대폭 상승
				textString << tempText[23];
				textString << 2;
				textString << tempText[14];
				GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() + 2);
				GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() + 2);
				GameData::getPlayer()->addHit(2);
				GameData::getPlayer()->addEva(2);
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() - 4);
			}
			else { //악 게이지가 높을때(체력소모)
				int randStatus = rand() % 5 + GameData::getInGameData()->getLevel();
				textString << tempText[20];
				if (randStatus == 0)
					textString << tempText[22];
				else {
					textString << tempText[11];
					textString << randStatus;
					textString << tempText[17];
					GameData::getPlayer()->addHP(-randStatus);
					GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 1);
				}
			}
		}
	}
	else if (GameData::getMapData()->getType() == 4) { //악마방
		if (caseNum % 3 == 0) { //축복(능력치증가)
			textString << tempText[3];
			if (GameData::getPlayer()->getAngel() >= 0 && GameData::getPlayer()->getAngel() < 50) { //소폭 상승
				textString << tempText[13];
				textString << 1;
				textString << tempText[16];
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 1);
			}
			else if (GameData::getPlayer()->getAngel() >= 50) { //대폭 상승
				textString << tempText[13];
				textString << 2;
				textString << tempText[16];
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 2);
			}
			else { //악 게이지가 높을때(체력소모)
				int randStatus = rand() % 5 + GameData::getInGameData()->getLevel();
				textString << tempText[21];
				if (randStatus == 0)
					textString << tempText[22];
				else {
					textString << tempText[11];
					textString << randStatus;
					textString << tempText[17];
					GameData::getPlayer()->addHP(-randStatus);
				}
			}
		}
		else if (caseNum % 3 == 1) { //거래
			textString << "악마와 거래를 할 수 없다.";
		}
		else { //평가(대화게이지 대폭)(올스택 소폭감소)
			textString << tempText[5];
			if (GameData::getPlayer()->getAngel() >= 0 && GameData::getPlayer()->getAngel() < 50) { //소폭 상승
				textString << tempText[23];
				textString << 1;
				textString << tempText[15];
				GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() - 1);
				GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() - 1);
				GameData::getPlayer()->addHit(-1);
				GameData::getPlayer()->addEva(-1);
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 2);
			}
			else if (GameData::getPlayer()->getAngel() >= 50) { //대폭 상승
				textString << tempText[23];
				textString << 2;
				textString << tempText[15];
				GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() - 2);
				GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() - 2);
				GameData::getPlayer()->addHit(-2);
				GameData::getPlayer()->addEva(-2);
				GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 4);
			}
			else { //선 게이지가 높을때(체력소모)
				int randStatus = rand() % 5 + GameData::getInGameData()->getLevel();
				textString << tempText[21];
				if (randStatus == 0)
					textString << tempText[22];
				else {
					textString << tempText[11];
					textString << randStatus;
					textString << tempText[17];
					GameData::getPlayer()->addHP(-randStatus);
					GameData::getPlayer()->setCommuPower(GameData::getPlayer()->getCommuPower() + 1);
				}
			}
		}
	}
	else if (GameData::getMapData()->getType() == 5) { //상자방
		int getItemIndex = rand() % (100 + (GameData::getInGameData()->getLevel() * 10)); //난이도마다 다름
		textString << tempText[6]; //상자를 열었다.
		if (getItemIndex < 15) { //희귀장비아이템 획득
			int item1[5] = { 20,27,28,29,32 };
			int resultItem = item1[rand() % 5]; //결과아이템
			textString << GameData::getInGameData()->getItemName(resultItem); //획득 아이템 이름
			textString << tempText[18]; //을 획득했다.

			itemImage = GameData::getInGameData()->getItemImage(resultItem);
			itemImage->setPosition(Point(140 + (100*GameData::getInGameData()->getRoomNum()), 500));
			addChild(itemImage, 3);
			itemImage->runAction(RepeatForever::create(Sequence::create(
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				nullptr)));

			GameData::getPlayer()->addItem(resultItem); //인벤토리에 아이템 추가
		}
		else if (getItemIndex >= 15 && getItemIndex < 50) { //일반장비아이템 획득
			int item1[5] = { 21,22,23,24,31 };
			int resultItem = item1[rand() % 5]; //결과아이템
			textString << GameData::getInGameData()->getItemName(resultItem); //획득 아이템 이름
			textString << tempText[18]; //을 획득했다.

			itemImage = GameData::getInGameData()->getItemImage(resultItem);
			itemImage->setPosition(Point(140 + (100 * GameData::getInGameData()->getRoomNum()), 500));
			addChild(itemImage, 3);
			itemImage->runAction(RepeatForever::create(Sequence::create(
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				nullptr)));

			GameData::getPlayer()->addItem(resultItem); //인벤토리에 아이템 추가
		}
		else if (getItemIndex >= 50 && getItemIndex < 70) { //소모아이템 획득
			int resultItem = (rand() % 8) + 40; //결과아이템
			textString << GameData::getInGameData()->getItemName(resultItem); //획득 아이템 이름
			textString << tempText[18]; //을 획득했다.

			itemImage = GameData::getInGameData()->getItemImage(resultItem);
			itemImage->setPosition(Point(140 + (100 * GameData::getInGameData()->getRoomNum()), 500));
			addChild(itemImage, 3);
			itemImage->runAction(RepeatForever::create(Sequence::create(
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseIn::create(MoveBy::create(0.5f, Vec2(0, -30)), 0.6f),
				EaseOut::create(MoveBy::create(0.5f, Vec2(0, 30)), 0.6f),
				nullptr)));

			GameData::getPlayer()->addItem(resultItem); //인벤토리에 아이템 추가
		}
		else { //아무것도 얻지 못함(배고픔 소모)
			int hunGage = (rand() % 5) + GameData::getInGameData()->getLevel(); //난이도 별로 추가 소모
			textString << tempText[19];
			if (hunGage == 0)
				textString << tempText[22];
			else {
				textString << "\n";
				if (GameData::getPlayer()->getHunger() == 0) {
					textString << tempText[11];
					textString << (hunGage*2);
					textString << tempText[17];
				}
				else {
					textString << tempText[12];
					textString << hunGage;
					textString << tempText[17];
				}
				GameData::getPlayer()->addHunger(-(hunGage)); //배고픔 소모
			}
		}
	}
	contentLabel->setString(textString.str()); //최종 텍스트 삽입
	DatabaseManager::getInstance()->saveAllData();
}

void EventScene::NextTextClicked(cocos2d::Ref * pSender)
{
	log("next button clicked!");
	if (GameData::getInGameData()->getCommuNum() == GameData::getInGameData()->getTextManager()->getTextList()->lastNodeNum()) {
		GameData::getInGameData()->setCommuCase(0);
		GameData::getInGameData()->setCommuNum(0);
		deleteCommuPane();
		createChoicePane();
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

void EventScene::PreviousTextClicked(cocos2d::Ref * pSender)
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

void EventScene::SkipClicked(cocos2d::Ref * pSender)
{
	log("skip button clicked!");
	GameData::getInGameData()->setCommuCase(0);
	GameData::getInGameData()->setCommuNum(0);
	deleteCommuPane();
	createChoicePane();
}

void EventScene::okClicked(cocos2d::Ref * pSender)
{
	log("ok button clicked!");
	if (choiceNum == 0) {
		choiceNum++;
		removeChildByName("choiceLayer");
		createCommuPane();
	}
	else if (choiceNum == 1) {
		auto whiteScreen = CCSprite::create("gfx/backGround/whiteScreen.png");
		whiteScreen->setName("whiteScreen");
		whiteScreen->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		whiteScreen->setOpacity(0);
		addChild(whiteScreen, 6);
		whiteScreen->runAction(Sequence::create(
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			FadeOut::create(1.0f),
			nullptr));
		CCCallFunc * callFunc = CCCallFuncN::create(this, callfuncN_selector(EventScene::setChoicePane));
		this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1.0f), callFunc));
		choiceNum++;
		GameData::getMapData()->setIsItemParm(false);
	}
	else if (choiceNum == 2) {
		auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
		Director::getInstance()->replaceScene(GameScene);
	}
}

void EventScene::cancelClicked(cocos2d::Ref * pSender)
{
	log("cancel button clicked!");
	if (choiceNum == 0) {
		auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
		Director::getInstance()->replaceScene(GameScene);
	}
	else if (choiceNum == 1) {
		GameData::getMapData()->setIsItemParm(false);
		auto GameScene = CCTransitionFadeTR::create(0.5f, GameScene::createScene());
		Director::getInstance()->replaceScene(GameScene);
	}
}