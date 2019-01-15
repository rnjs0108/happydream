#include "ItemScene.h"
#include "DatabaseManager.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;
using namespace cocostudio::timeline;

bool isEquipClick = false;
int cellIndex = 0;
int itemValue = 0;

Scene* ItemScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ItemScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool ItemScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}
	log("ItemScene Load Start item value : %d", GameData::getPlayer()->someItemIndex(itemValue));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto itemSceneBG = CCSprite::create("gfx/backGround/itemSceneBG.png");
	itemSceneBG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto statusImage = Layer::create();
	statusImage->setName("statusImage");
	statusImage->setPosition(Point(0, 0));
	auto HP_Gage = CCSprite::create("gfx/object/HP_Gage.png");
	HP_Gage->setName("HP_Gage");
	HP_Gage->setAnchorPoint(Vec2(0, 0));
	HP_Gage->setPosition(Point(40, 755));
	auto Hunger_Gage = CCSprite::create("gfx/object/Hunger_Gage.png");
	Hunger_Gage->setName("Hunger_Gage");
	Hunger_Gage->setAnchorPoint(Vec2(0, 0));
	Hunger_Gage->setPosition(Point(40, 730));
	auto Devil_Gage = CCSprite::create("gfx/object/Devil_Gage.png");
	Devil_Gage->setName("Devil_Gage");
	Devil_Gage->setAnchorPoint(Vec2(0, 0));
	Devil_Gage->setPosition(Point(40, 705));
	auto Angel_Gage = CCSprite::create("gfx/object/Angel_Gage.png");
	Angel_Gage->setName("Angel_Gage");
	Angel_Gage->setAnchorPoint(Vec2(0, 0));
	Angel_Gage->setPosition(Point(40, 705));
	auto HP_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	HP_label->setName("HP_label");
	HP_label->setPosition(Point(165, 765));
	HP_label->setColor(Color3B::BLACK);
	auto Hunger_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	Hunger_label->setName("Hunger_label");
	Hunger_label->setPosition(Point(165, 740));
	Hunger_label->setColor(Color3B::BLACK);
	auto DA_label = Label::createWithTTF(textString.str(), "fonts/arial.ttf", 20, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	DA_label->setName("DA_label");
	DA_label->setPosition(Point(165, 715));
	DA_label->setColor(Color3B::BLACK);
	HP_Gage->setScaleX(float(GameData::getPlayer()->getHP() / Player::MAX_HP));
	Hunger_Gage->setScaleX((float)GameData::getPlayer()->getHunger() / Player::MAX_HUNGER);
	Devil_Gage->setScaleX((float(GameData::getPlayer()->getDevil() / 100.0f)));
	Angel_Gage->setScaleX((float(GameData::getPlayer()->getAngel() / 100.0f)));

	auto statBox = CCSprite::create("gfx/object/statusBox.png");
	statBox->setPosition(Point(105, 740));
	auto gageBar1 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar1->setScaleX(1.2f);
	gageBar1->setPosition(Point(90, 765));
	auto gageBar2 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar2->setScaleX(1.2f);
	gageBar2->setPosition(Point(90, 740));
	auto gageBar3 = CCSprite::create("gfx/object/Gage_Bar.png");
	gageBar3->setScaleX(1.2f);
	gageBar3->setPosition(Point(90, 715));

	statusImage->addChild(statBox, 0);
	statusImage->addChild(HP_Gage, 1);
	statusImage->addChild(Hunger_Gage, 1);
	statusImage->addChild(Devil_Gage, 1);
	statusImage->addChild(Angel_Gage, 1);
	statusImage->addChild(gageBar1, 2);
	statusImage->addChild(gageBar2, 2);
	statusImage->addChild(gageBar3, 2);
	statusImage->addChild(HP_label, 3);
	statusImage->addChild(Hunger_label, 3);
	statusImage->addChild(DA_label, 3);

	auto itemExpPane = CCSprite::create("gfx/object/itemExpPane.png");
	itemExpPane->setName("itemExpPane");
	itemExpPane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 60));
	auto itemName_label = Label::createWithTTF("", "fonts/THE_Oegyeinseolmyeongseo.ttf", 26, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemName_label->setName("itemName_label");
	itemName_label->setPosition(Point(235, 280));
	itemName_label->setColor(Color3B::BLACK);
	auto itemExp_label = Label::createWithTTF("", "fonts/THELeft.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemExp_label->setName("itemExp_label");
	itemExp_label->setPosition(Point(180, 180));
	itemExp_label->setColor(Color3B::BLACK);
	auto itemPointExp_label = Label::createWithTTF("", "fonts/NanumGothic.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemPointExp_label->setName("itemPointExp_label");
	itemPointExp_label->setPosition(Point(180, 120));
	itemPointExp_label->setColor(Color3B(30,90,30));
	auto itemExpBorder = CCSprite::create("gfx/object/itemExpBorder.png");
	itemExpBorder->setName("itemExpBorder");
	itemExpBorder->setPosition(Point(90, 310));
	auto itemExpImage = CCSprite::create("gfx/item/empty.png");
	itemExpImage->setName("itemExpImage");
	itemExpImage->setAnchorPoint(Point::ZERO);
	itemExpImage->setPosition(Point::ZERO);
	itemExpBorder->addChild(itemExpImage);

	itemExpPane->addChild(itemExpBorder);
	itemExpPane->addChild(itemName_label);
	itemExpPane->addChild(itemExp_label);
	itemExpPane->addChild(itemPointExp_label);

	auto ATK_label = Label::createWithTTF("ATK  1", "fonts/MarkerFelt.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	ATK_label->setName("ATK_label");
	ATK_label->setPosition(Point(70, 640));
	ATK_label->setColor(Color3B::YELLOW);
	auto ATKp_label = Label::createWithTTF("(+ 0)", "fonts/MarkerFelt.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	ATKp_label->setName("ATKp_label");
	ATKp_label->setPosition(Point(150, 640));
	ATKp_label->setColor(Color3B::GREEN);
	auto DEF_label = Label::createWithTTF("DEF  0", "fonts/MarkerFelt.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	DEF_label->setName("DEF_label");
	DEF_label->setPosition(Point(70, 590));
	DEF_label->setColor(Color3B::YELLOW);
	auto DEFp_label = Label::createWithTTF("(+ 0)", "fonts/MarkerFelt.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	DEFp_label->setName("DEFp_label");
	DEFp_label->setPosition(Point(150, 590));
	DEFp_label->setColor(Color3B::GREEN);
	auto HIT_label = Label::createWithTTF("HIT  1", "fonts/MarkerFelt.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	HIT_label->setName("HIT_label");
	HIT_label->setPosition(Point(visibleSize.width / 2 + 70, 640));
	HIT_label->setColor(Color3B::YELLOW);
	auto HITp_label = Label::createWithTTF("(+ 0)", "fonts/MarkerFelt.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	HITp_label->setName("HITp_label");
	HITp_label->setPosition(Point(visibleSize.width / 2 + 150, 640));
	HITp_label->setColor(Color3B::GREEN);
	auto EVA_label = Label::createWithTTF("EVA  1", "fonts/MarkerFelt.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	EVA_label->setName("EVA_label");
	EVA_label->setPosition(Point(visibleSize.width / 2 + 70, 590));
	EVA_label->setColor(Color3B::YELLOW);
	auto EVAp_label = Label::createWithTTF("(+ 0)", "fonts/MarkerFelt.ttf", 18, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	EVAp_label->setName("EVAp_label");
	EVAp_label->setPosition(Point(visibleSize.width / 2 + 150, 590));
	EVAp_label->setColor(Color3B::GREEN);

	auto itemValue_label = Label::createWithTTF("전체아이템", "fonts/THELeft.ttf", 24, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemValue_label->setName("itemValue_label");
	itemValue_label->setPosition(Point(visibleSize.width / 2 + 90, 180));
	itemValue_label->setColor(Color3B::BLACK);
	auto itemNum_label = Label::createWithTTF("0개", "fonts/THELeft.ttf", 22, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	itemNum_label->setName("itemNum_label");
	itemNum_label->setPosition(Point(visibleSize.width / 2 + 160, 180));
	itemNum_label->setColor(Color3B::BLACK);

	auto statusLayer = Layer::create();
	statusLayer->setName("statusLayer");
	statusLayer->setPosition(Point(0, 0));
	statusLayer->addChild(ATK_label);
	statusLayer->addChild(DEF_label);
	statusLayer->addChild(HIT_label);
	statusLayer->addChild(EVA_label);
	statusLayer->addChild(ATKp_label);
	statusLayer->addChild(DEFp_label);
	statusLayer->addChild(HITp_label);
	statusLayer->addChild(EVAp_label);
	statusLayer->addChild(itemValue_label);
	statusLayer->addChild(itemNum_label);

	auto EquipBG1 = CCSprite::create("gfx/object/equipBottom.png");
	EquipBG1->setName("EquipBG1");
	EquipBG1->setPosition(Point(260, 740));
	auto EquipBG2 = CCSprite::create("gfx/object/equipBottom.png");
	EquipBG2->setName("EquipBG2");
	EquipBG2->setPosition(Point(360, 740));
	auto EquipItemImage1 = CCSprite::create("gfx/item/empty.png");
	EquipItemImage1->setName("EquipItemImage1");
	EquipItemImage1->setAnchorPoint(Point::ZERO);
	EquipItemImage1->setPosition(Point::ZERO);
	auto EquipItemImage2 = CCSprite::create("gfx/item/empty.png");
	EquipItemImage2->setName("EquipItemImage2");
	EquipItemImage2->setAnchorPoint(Point::ZERO);
	EquipItemImage2->setPosition(Point::ZERO);
	EquipBG1->addChild(EquipItemImage1);
	EquipBG2->addChild(EquipItemImage2);
	
	auto EquipItemBorder = CCSprite::create("gfx/object/equipPane.png");
	EquipItemBorder->setName("EquipItemBorder");
	EquipItemBorder->runAction(RepeatForever::create(
		Sequence::create(
			FadeOut::create(0.5f),
			FadeIn::create(0.5f),
			nullptr)));
	EquipItemBorder->setVisible(false);
	
	auto UsedButton = MenuItemImage::create(
		"gfx/icon/useButton_n.png",
		"gfx/icon/useButton_n.png",
		CC_CALLBACK_1(ItemScene::useItemClicked, this));
	UsedButton->setName("UsedButton");
	UsedButton->setPosition(Point(410, 400));
	auto DeleteButton = MenuItemImage::create(
		"gfx/icon/deleteButton_lock.png",
		"gfx/icon/deleteButton_lock.png",
		CC_CALLBACK_1(ItemScene::dropItemClicked, this));
	DeleteButton->setName("DeleteButton");
	DeleteButton->setPosition(Point(410, 260));
	auto QuitButton = MenuItemImage::create(
		"gfx/icon/cancelButton.png",
		"gfx/icon/cancelButton_clicked.png",
		CC_CALLBACK_1(ItemScene::quitClicked, this));
	QuitButton->setName("QuitButton");
	QuitButton->setPosition(Point(visibleSize.width - 35, 765));
	auto EquipButton1 = MenuItemImage::create(
		"gfx/icon/equipButton1.png",
		"gfx/icon/equipButton1.png",
		CC_CALLBACK_1(ItemScene::equipItem1Clicked, this));
	EquipButton1->setName("EquipButton1");
	EquipButton1->setPosition(Point(260, 740));
	auto EquipButton2 = MenuItemImage::create(
		"gfx/icon/equipButton2.png",
		"gfx/icon/equipButton2.png",
		CC_CALLBACK_1(ItemScene::equipItem2Clicked, this));
	EquipButton2->setName("EquipButton2");
	EquipButton2->setPosition(Point(360, 740));
	auto leftButton = MenuItemImage::create(
		"gfx/icon/itemLeftButton.png",
		"gfx/icon/itemLeftButton.png",
		CC_CALLBACK_1(ItemScene::leftClicked, this));
	leftButton->setName("leftButton");
	leftButton->setPosition(Point(20, 83));
	auto rightButton = MenuItemImage::create(
		"gfx/icon/itemRightButton.png",
		"gfx/icon/itemRightButton.png",
		CC_CALLBACK_1(ItemScene::rightClicked, this));
	rightButton->setName("rightButton");
	rightButton->setPosition(Point(460, 83));
	auto pMenu = Menu::create(QuitButton,UsedButton, DeleteButton, EquipButton1, EquipButton2, leftButton, rightButton, NULL);
	pMenu->setName("pMenu");
	pMenu->setPosition(Point(0, 0));

	auto viewAllItemButton = MenuItemImage::create(
		"gfx/icon/viewAllItemButton.png",
		"gfx/icon/viewAllItemButton_clicked.png",
		CC_CALLBACK_1(ItemScene::viewAllItemClicked, this));
	viewAllItemButton->setName("viewAllItemButton");
	viewAllItemButton->setPosition(Point(50, 180));
	auto viewEquipItemButton = MenuItemImage::create(
		"gfx/icon/viewEquipItemButton.png",
		"gfx/icon/viewEquipItemButton_clicked.png",
		CC_CALLBACK_1(ItemScene::viewEquipItemClicked, this));
	viewEquipItemButton->setName("viewEquipItemButton");
	viewEquipItemButton->setPosition(Point(110, 180));
	auto viewFoodItemButton = MenuItemImage::create(
		"gfx/icon/viewFoodItemButton.png",
		"gfx/icon/viewFoodItemButton_clicked.png",
		CC_CALLBACK_1(ItemScene::viewFoodItemClicked, this));
	viewFoodItemButton->setName("viewFoodItemButton");
	viewFoodItemButton->setPosition(Point(170, 180));
	auto viewMaterialItemButton = MenuItemImage::create(
		"gfx/icon/viewMaterialItemButton.png",
		"gfx/icon/viewMaterialItemButton_clicked.png",
		CC_CALLBACK_1(ItemScene::viewMaterialItemClicked, this));
	viewMaterialItemButton->setName("viewMaterialItemButton");
	viewMaterialItemButton->setPosition(Point(230, 180));

	auto viewMenu = Menu::create(viewAllItemButton, viewEquipItemButton, viewFoodItemButton, viewMaterialItemButton, NULL);
	viewMenu->setName("viewMenu");
	viewMenu->setPosition(Point(0, 0));

	auto tableView = TableView::create(this, Size(400,100));
	tableView->setName("tableView");
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView->setPosition(Point(40, 34));
	tableView->setDelegate(this);
	tableView->reloadData();
	UsedButton->setEnabled(false);
	DeleteButton->setEnabled(false);

	addChild(itemSceneBG, 0);
	addChild(tableView, 1);
	addChild(itemExpPane, 2);
	addChild(statusImage, 2);
	addChild(statusLayer, 3);
	addChild(EquipBG1, 3);
	addChild(EquipBG2, 3);
	addChild(pMenu, 4);
	addChild(viewMenu, 4);
	addChild(EquipItemBorder, 5);

	setEquipImage();
	setText();
	setGageScale();

	return true;
}

void ItemScene::setText()
{
	auto ATK_label = getChildByName("statusLayer")->getChildByName<Label*>("ATK_label");
	auto DEF_label = getChildByName("statusLayer")->getChildByName<Label*>("DEF_label");
	auto HIT_label = getChildByName("statusLayer")->getChildByName<Label*>("HIT_label");
	auto EVA_label = getChildByName("statusLayer")->getChildByName<Label*>("EVA_label");
	auto ATKp_label = getChildByName("statusLayer")->getChildByName<Label*>("ATKp_label");
	auto DEFp_label = getChildByName("statusLayer")->getChildByName<Label*>("DEFp_label");
	auto HITp_label = getChildByName("statusLayer")->getChildByName<Label*>("HITp_label");
	auto EVAp_label = getChildByName("statusLayer")->getChildByName<Label*>("EVAp_label");
	auto HP_label = getChildByName("statusImage")->getChildByName<Label*>("HP_label");
	auto Hunger_label = getChildByName("statusImage")->getChildByName<Label*>("Hunger_label");
	auto DA_label = getChildByName("statusImage")->getChildByName<Label*>("DA_label");
	auto itemValue_label = getChildByName("statusLayer")->getChildByName<Label*>("itemValue_label");
	auto itemNum_label = getChildByName("statusLayer")->getChildByName<Label*>("itemNum_label");
	
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
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getAttack();
	ATK_label->setString("ATK  "+ textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getDepence();
	DEF_label->setString("DEF  " + textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getHit();
	HIT_label->setString("HIT  " + textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->getEva();
	EVA_label->setString("EVA  " + textString.str());
	textString.str("");
	textString.clear();
	if (GameData::getPlayer()->getAttack_p() >= 0)
		textString << "(+ " << GameData::getPlayer()->getAttack_p();
	else
		textString << "(- " << -GameData::getPlayer()->getAttack_p();
	ATKp_label->setString(textString.str()+")");
	textString.str("");
	textString.clear();
	if (GameData::getPlayer()->getDepence_p() >= 0)
		textString << "(+ " << GameData::getPlayer()->getDepence_p();
	else
		textString << "(- " << -GameData::getPlayer()->getDepence_p();
	DEFp_label->setString(textString.str() + ")");
	textString.str("");
	textString.clear();
	if (GameData::getPlayer()->getHit_p() >= 0)
		textString << "(+ " << GameData::getPlayer()->getHit_p();
	else
		textString << "(- " << -GameData::getPlayer()->getHit_p();
	HITp_label->setString(textString.str() + ")");
	textString.str("");
	textString.clear();
	if (GameData::getPlayer()->getEva_p() >= 0)
		textString << "(+ " << GameData::getPlayer()->getEva_p();
	else
		textString << "(- " << -GameData::getPlayer()->getEva_p();
	EVAp_label->setString(textString.str() + ")");
	textString.str("");
	textString.clear();
	if(itemValue == 0)
		textString << "전체아이템";
	else if (itemValue == 1)
		textString << "장비아이템";
	else if (itemValue == 2)
		textString << "소모아이템";
	else if (itemValue == 3)
		textString << "재료아이템";
	itemValue_label->setString(textString.str());
	textString.str("");
	textString.clear();
	textString << GameData::getPlayer()->someItemIndex(itemValue);
	textString << "개";
	itemNum_label->setString(textString.str());
}

void ItemScene::setGageScale()
{
	auto HP_Gage = getChildByName("statusImage")->getChildByName<CCSprite*>("HP_Gage");
	auto Hunger_Gage = getChildByName("statusImage")->getChildByName<CCSprite*>("Hunger_Gage");
	auto Devil_Gage = getChildByName("statusImage")->getChildByName<CCSprite*>("Devil_Gage");
	auto Angel_Gage = getChildByName("statusImage")->getChildByName<CCSprite*>("Angel_Gage");
	HP_Gage->runAction(ScaleTo::create(0.5f, float(GameData::getPlayer()->getHP() / Player::MAX_HP), 1));
	Hunger_Gage->runAction(ScaleTo::create(0.5f, ((float)GameData::getPlayer()->getHunger() / Player::MAX_HUNGER), 1));
	Devil_Gage->runAction(ScaleTo::create(0.5f, (float(GameData::getPlayer()->getDevil() / 100.0f)), 1));
	Angel_Gage->runAction(ScaleTo::create(0.5f, (float(GameData::getPlayer()->getAngel() / 100.0f)), 1));
}

void ItemScene::setButtonVisible()
{
	auto UsedButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("UsedButton");
	auto DeleteButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("DeleteButton");
	auto itemExpImage = getChildByName("itemExpPane")->getChildByName("itemExpBorder")->getChildByName<CCSprite*>("itemExpImage");
	if (!isEquipClick) { //아이템창 클릭 시
		if (GameData::getPlayer()->getItemBag(cellIndex)->getItemNum() == 0) { //아이템이 없는노드
			UsedButton->setEnabled(false);
			DeleteButton->setEnabled(false);
		}
		else {
			itemExpImage->setTexture(GameData::getInGameData()->getItemImage(GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType())->getTexture());
			DeleteButton->setNormalImage(CCSprite::create("gfx/icon/deleteButton.png"));
			DeleteButton->setSelectedImage(CCSprite::create("gfx/icon/deleteButton_clicked.png"));
			DeleteButton->setEnabled(true);
			if (GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getCanUse()) { //사용가능한 아이템
				if (GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType() >= 20 && GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType() < 40) { //장비아이템이면
					if (GameData::getPlayer()->isEquipFull()) {
						UsedButton->setEnabled(false);
						UsedButton->setNormalImage(CCSprite::create("gfx/icon/useButton_n.png"));
						UsedButton->setSelectedImage(CCSprite::create("gfx/icon/useButton_n.png"));
					}
					else{
						UsedButton->setEnabled(true);
						UsedButton->setNormalImage(CCSprite::create("gfx/icon/equipClickButton.png"));
						UsedButton->setSelectedImage(CCSprite::create("gfx/icon/equipClickButton_clicked.png"));
					}
				}
				else { //소비아이템인 경우
					UsedButton->setEnabled(true);
					UsedButton->setNormalImage(CCSprite::create("gfx/icon/useButton.png"));
					UsedButton->setSelectedImage(CCSprite::create("gfx/icon/useButton_clicked.png"));
				}
			}
			else { //사용불가 아이템인 경우
				UsedButton->setEnabled(false);
				UsedButton->setNormalImage(CCSprite::create("gfx/icon/useButton_n.png"));
				UsedButton->setSelectedImage(CCSprite::create("gfx/icon/useButton_n.png"));
			}
		}
	}
	else {
		if (cellIndex < 2) { //장비 해제 아이콘
			itemExpImage->setTexture(GameData::getInGameData()->getItemImage(GameData::getPlayer()->getEquipItem(cellIndex)->getType())->getTexture());
			UsedButton->setNormalImage(CCSprite::create("gfx/icon/takeOffButton.png"));
			UsedButton->setSelectedImage(CCSprite::create("gfx/icon/takeOffButton_clicked.png"));
			DeleteButton->setNormalImage(CCSprite::create("gfx/icon/deleteButton_lock.png"));
			DeleteButton->setSelectedImage(CCSprite::create("gfx/icon/deleteButton_lock.png"));
			UsedButton->setEnabled(true);
			DeleteButton->setEnabled(false);
		}
	}
}

void ItemScene::setButtonHide()
{
	auto itemName_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemName_label");
	auto itemExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemExp_label");
	auto itemPointExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemPointExp_label");
	auto UsedButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("UsedButton");
	auto DeleteButton = getChildByName("pMenu")->getChildByName<MenuItemImage*>("DeleteButton");
	auto itemExpImage = getChildByName("itemExpPane")->getChildByName("itemExpBorder")->getChildByName<CCSprite*>("itemExpImage");
	UsedButton->setNormalImage(CCSprite::create("gfx/icon/useButton_n.png"));
	UsedButton->setSelectedImage(CCSprite::create("gfx/icon/useButton_n.png"));
	DeleteButton->setNormalImage(CCSprite::create("gfx/icon/deleteButton_lock.png"));
	DeleteButton->setSelectedImage(CCSprite::create("gfx/icon/deleteButton_lock.png"));
	itemExpImage->setTexture("gfx/item/empty.png");
	UsedButton->setEnabled(false);
	DeleteButton->setEnabled(false);
	textString.str(""); textString.clear();
	itemName_label->setString(textString.str());
	itemExp_label->setString(textString.str());
	itemPointExp_label->setString(textString.str());
}

void ItemScene::setEquipImage()
{
	auto EquipItemImage1 = getChildByName("EquipBG1")->getChildByName<CCSprite*>("EquipItemImage1");
	auto EquipItemImage2 = getChildByName("EquipBG2")->getChildByName<CCSprite*>("EquipItemImage2");
	if (GameData::getPlayer()->getEquipItem(0) != NULL)
		EquipItemImage1->setTexture(GameData::getInGameData()->getItemImage(GameData::getPlayer()->getEquipItem(0)->getType())->getTexture());
	else
		EquipItemImage1->setTexture("gfx/item/empty.png");
	if (GameData::getPlayer()->getEquipItem(1) != NULL)
		EquipItemImage2->setTexture(GameData::getInGameData()->getItemImage(GameData::getPlayer()->getEquipItem(1)->getType())->getTexture());
	else
		EquipItemImage2->setTexture("gfx/item/empty.png");
}

void ItemScene::useItemClicked(cocos2d::Ref * pSender) //아이템 사용
{
	log("use clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	auto EquipItemBorder = getChildByName<CCSprite*>("EquipItemBorder");
	auto offset = tableView->getContentOffset();
	int test = GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType();
	if (!isEquipClick) {
		if (GameData::getPlayer()->getItemBag(cellIndex)->getItemNum() != 0)
			if (GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getCanUse()) {
				if (GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType() >= 20 && GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType() < 40) {
					if (!GameData::getPlayer()->isEquipFull()) { //장비 장착
						GameData::getPlayer()->setEquipItem(cellIndex);
					}
				}
				else { //아이템 사용
					GameData::getPlayer()->getItemBag(cellIndex)->useItem();
				}
			}
	}
	else { //장착 해제
		if (cellIndex < 2) {
			GameData::getPlayer()->takeOffItem(cellIndex);
			EquipItemBorder->setVisible(false);
			setButtonHide();
		}
	}
	tableView->reloadData();
	if (GameData::getPlayer()->getItemBag(cellIndex)->getItem() == NULL || test != GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType()) {
		setButtonHide();
		if (offset.x > 400 || (GameData::getPlayer()->someItemIndex(itemValue) - 4)) {
			tableView->setContentOffset(Vec2(0, 0));
		}
		else if ((GameData::getPlayer()->someItemIndex(itemValue) - cellIndex) < 4 )
			tableView->setContentOffset(Vec2(-100 * (GameData::getPlayer()->someItemIndex(itemValue) - 4), 0));
		else
			tableView->setContentOffset(offset);
	}
	else
		tableView->setContentOffset(offset);
	DatabaseManager::getInstance()->saveAllData();
	setEquipImage();
	setText();
	setGageScale();
}

void ItemScene::dropItemClicked(cocos2d::Ref * pSender) //아이템 삭제
{
	log("drop clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	if (!isEquipClick) {
		auto offset = tableView->getContentOffset();
		int test = GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType();
		GameData::getPlayer()->getItemBag(cellIndex)->dropitem(1);
		tableView->reloadData();
		if (GameData::getPlayer()->getItemBag(cellIndex)->getItem() == NULL || test != GameData::getPlayer()->getItemBag(cellIndex)->getItem()->getType()) {
			setButtonHide();
			if (offset.x > 400 || (GameData::getPlayer()->someItemIndex(itemValue) - 4)) {
				tableView->setContentOffset(Vec2(0, 0));
			}
			else if ((GameData::getPlayer()->someItemIndex(itemValue) - cellIndex) < 4)
				tableView->setContentOffset(Vec2(-100 * (GameData::getPlayer()->someItemIndex(itemValue) - 4), 0));
			else
				tableView->setContentOffset(offset);
		}
		else
			tableView->setContentOffset(offset);
		setText();
		setGageScale();
	}
	DatabaseManager::getInstance()->saveItemList();
}

void ItemScene::quitClicked(cocos2d::Ref * pSender) //나가기 버튼
{
	log("quit clicked!");
	auto gameScene = CCTransitionFadeUp::create(0.5f, GameScene::createScene());
	Director::getInstance()->replaceScene(gameScene);
}

void ItemScene::leftClicked(cocos2d::Ref * pSender)
{
	log("left clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	if (GameData::getPlayer()->PlayerItemIndex() > 4)
		tableView->setContentOffset(Vec2(0, 0));
}

void ItemScene::rightClicked(cocos2d::Ref * pSender)
{
	log("right clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	if(GameData::getPlayer()->PlayerItemIndex() > 4)
		tableView->setContentOffset(Vec2(-100*(GameData::getPlayer()->someItemIndex(itemValue) - 4), 0));
}

void ItemScene::equipItem1Clicked(cocos2d::Ref * pSender)
{
	log("equip1 clicked!");
	if (GameData::getPlayer()->getEquipItem(0) != NULL) {
		auto itemName_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemName_label");
		auto itemExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemExp_label");
		auto itemPointExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemPointExp_label");
		auto EquipItemBorder = getChildByName<CCSprite*>("EquipItemBorder");
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(0)->getName();
		itemName_label->setString(textString.str());
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(0)->getExp();
		itemExp_label->setString(textString.str());
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(0)->getPointExp();
		itemPointExp_label->setString(textString.str());
		isEquipClick = true;
		cellIndex = 0;
		EquipItemBorder->setPosition(Point(260, 740));
		EquipItemBorder->setVisible(true);
		setButtonVisible();
	}
}

void ItemScene::equipItem2Clicked(cocos2d::Ref * pSender)
{
	log("equip2 clicked!");
	if (GameData::getPlayer()->getEquipItem(1) != NULL) {
		auto itemName_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemName_label");
		auto itemExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemExp_label");
		auto itemPointExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemPointExp_label");
		auto EquipItemBorder = getChildByName<CCSprite*>("EquipItemBorder");
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(1)->getName();
		itemName_label->setString(textString.str());
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(1)->getExp();
		itemExp_label->setString(textString.str());
		textString.str(""); textString.clear();
		textString << GameData::getPlayer()->getEquipItem(1)->getPointExp();
		itemPointExp_label->setString(textString.str());
		isEquipClick = true;
		cellIndex = 1;
		EquipItemBorder->setPosition(Point(360, 740));
		EquipItemBorder->setVisible(true);
		setButtonVisible();
	}
}

void ItemScene::viewAllItemClicked(cocos2d::Ref * pSender)
{
	log("viewAllItem clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	itemValue = 0;
	tableView->reloadData();
	setText();
}

void ItemScene::viewEquipItemClicked(cocos2d::Ref * pSender)
{
	log("viewEquipItem clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	itemValue = 1;
	tableView->reloadData();
	setText();
}

void ItemScene::viewFoodItemClicked(cocos2d::Ref * pSender)
{
	log("viewFoodItem clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	itemValue = 2;
	tableView->reloadData();
	setText();
}

void ItemScene::viewMaterialItemClicked(cocos2d::Ref * pSender)
{
	log("viewMaterial clicked!");
	auto tableView = getChildByName<TableView*>("tableView");
	itemValue = 3;
	tableView->reloadData();
	setText();
}


Size ItemScene::tableCellSizeForIndex(TableView * table, ssize_t idx) //테이블셀의 개당 크기 지정
{
		return Size(100, 100);
}

TableViewCell * ItemScene::tableCellAtIndex(TableView * table, ssize_t idx) //셀 하나당 이미지등록
{
	//아이템 갯수를 입력
	TableViewCell* cell = table->dequeueCell();
	cell = new CustomTableViewCell();
	cell->autorelease();
	int num = GameData::getPlayer()->someItemBagIndex(itemValue, idx);
	CCSprite* sprite = GameData::getInGameData()->getItemImage(GameData::getPlayer()->getItemBag(num)->getItem()->getType());
	sprite->setAnchorPoint(Point::ZERO);
	sprite->setPosition(Point(0, 0));
	cell->addChild(sprite);
	auto string = String::createWithFormat("%d", GameData::getPlayer()->getItemBag(num)->getItemNum());
	auto label = Label::createWithTTF(string->getCString(), "fonts/arial.ttf", 24, Size(0, 0),
		TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setPosition(Point::ZERO);
	label->setAnchorPoint(Point::ZERO);
	cell->addChild(label);
	cell->setTag(num);
	return cell;
}

ssize_t ItemScene::numberOfCellsInTableView(TableView * table)
{
	return GameData::getPlayer()->someItemIndex(itemValue);
}

void ItemScene::tableCellTouched(TableView * table, TableViewCell * cell) //만약 테이블셀을 클릭한 경우
{
	auto itemName_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemName_label");
	auto itemExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemExp_label");
	auto itemPointExp_label = getChildByName("itemExpPane")->getChildByName<Label*>("itemPointExp_label");
	auto EquipItemBorder = getChildByName<CCSprite*>("EquipItemBorder");
	textString.str(""); textString.clear();
	textString << GameData::getPlayer()->getItemBag(cell->getTag())->getItem()->getName();
	itemName_label->setString(textString.str());
	textString.str(""); textString.clear();
	textString << GameData::getPlayer()->getItemBag(cell->getTag())->getItem()->getExp();
	itemExp_label->setString(textString.str());
	textString.str(""); textString.clear();
	textString << GameData::getPlayer()->getItemBag(cell->getTag())->getItem()->getPointExp();
	itemPointExp_label->setString(textString.str());
	cellIndex = cell->getTag();
	isEquipClick = false;
	log("Tag : %d, Item Index : %d, cell tag : %d", table->getTag(), GameData::getPlayer()->getItemBag(cell->getIdx())->getItem()->getType(), cell->getTag());
	EquipItemBorder->setVisible(false);
	setButtonVisible();
}
