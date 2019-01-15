#include "SavedGameData.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

Player* SavedGameData::player;

SavedGameData::SavedGameData()
{
	textManager = new TextManager();
	floorNum = GameData::MAX_FLOOR;
	roomNum = 1;
	level = 0;
	commuCase = 0;
	commuNum = 0;
	monsterKill = 0;
	tutoEnd = false;
	gameSetting();
}

SavedGameData::~SavedGameData()
{
}

void SavedGameData::gameSetting()
{
	//srand(time(NULL));
	if (floorNum == GameData::MAX_FLOOR) {
		mapData[0] = new MapData(0, false);
		mapData[1] = new MapData(0, false); //여기가 초기 화면
		mapData[2] = new MapData(0, false);
	}
	else if (floorNum == 1) {
		mapData[0] = new MapData(1, false);
		mapData[1] = new MapData(1, false);
		mapData[2] = new MapData(1, false);
	}
	else {
		int monNum = 3 - floorNum / (GameData::MAX_FLOOR / 2);
		for (int i = 0; i < 3; i++) {
			int eventRand = 0;
			if (i == 0 || i == 2) { //왼쪽이나 오른쪽방일때
				eventRand = rand() % (30 + GameData::getPlayer()->getAngel() + GameData::getPlayer()->getDevil());
				if (rand() % 100 >= 90) { //이벤트 확률 10퍼센트
					if (eventRand < 10 + GameData::getPlayer()->getAngel())
						mapData[i] = new MapData(3, false); //천사방
					else if (eventRand >= 10 + GameData::getPlayer()->getAngel() && eventRand < 20 + GameData::getPlayer()->getAngel())
						mapData[i] = new MapData(5, false); //상자방
					else
						mapData[i] = new MapData(4, false); //악마방
				}
				else { //일반 방 90퍼센트
					if (rand() % 100 < (70 + getLevel() * 10) - floorNum / 2) { //몬스터 나올 확률
						if (monNum > 0) { //몬스터 생성가능
							mapData[i] = new MapData(rand() % 6 + 6, true);
							monNum--;
						}
						else
							mapData[i] = new MapData(rand() % 6 + 6, false);
					}
					else //몬스터 안나옴
						mapData[i] = new MapData(rand() % 6 + 6, false);
				}
			}
			else //가운데 방일때
				if (monNum > 0) {
					mapData[i] = new MapData(2, true);
					monNum--;
				}
				else
					mapData[i] = new MapData(2, false);
		}
		
	}
	roomNum = 1;
}

CCSprite * SavedGameData::getItemImage(int n)
{
	CCSprite* sprite;
	switch (n) {
	case 0:
		sprite = Sprite::create("gfx/item/bond.png");
		break;
	case 1:
		sprite = Sprite::create("gfx/item/coin.png");
		break;
	case 2:
		sprite = Sprite::create("gfx/item/fabric.png");
		break;
	case 3:
		sprite = Sprite::create("gfx/item/board.png");
		break;
	case 4:
		sprite = Sprite::create("gfx/item/alcohol.png");
		break;
	case 5:
		sprite = Sprite::create("gfx/item/soap.png");
		break;
	case 6:
		sprite = Sprite::create("gfx/item/tape.png");
		break;
	case 7:
		sprite = Sprite::create("gfx/item/stapler.png");
		break;
	case 8:
		sprite = Sprite::create("gfx/item/rubber_band.png");
		break;
	case 9:
		sprite = Sprite::create("gfx/item/battery.png");
		break;
	case 10:
		sprite = Sprite::create("gfx/item/robot_broke.png");
		break;
	case 11:
		sprite = Sprite::create("gfx/item/lighter.png");
		break;
	case 20:
		sprite = Sprite::create("gfx/item/mes.png");
		break;
	case 21:
		sprite = Sprite::create("gfx/item/knife.png");
		break;
	case 22:
		sprite = Sprite::create("gfx/item/heartChain.png");
		break;
	case 23:
		sprite = Sprite::create("gfx/item/dear_doll.png");
		break;
	case 24:
		sprite = Sprite::create("gfx/item/mop.png");
		break;
	case 25:
		sprite = Sprite::create("gfx/item/macgyver.png");
		break;
	case 26:
		sprite = Sprite::create("gfx/item/rabbit_doll.png");
		break;
	case 27:
		sprite = Sprite::create("gfx/item/cloverChain.png");
		break;
	case 28:
		sprite = Sprite::create("gfx/item/book.png");
		break;
	case 29:
		sprite = Sprite::create("gfx/item/glove.png");
		break;
	case 30:
		sprite = Sprite::create("gfx/item/upgradeStapler.png");
		break;
	case 31:
		sprite = Sprite::create("gfx/item/fabricGlove.png");
		break;
	case 32:
		sprite = Sprite::create("gfx/item/spear.png");
		break;
	case 40:
		sprite = Sprite::create("gfx/item/biscuit.png");
		break;
	case 41:
		sprite = Sprite::create("gfx/item/soboruBread.png");
		break;
	case 42:
		sprite = Sprite::create("gfx/item/firstAidKit.png");
		break;
	case 43:
		sprite = Sprite::create("gfx/item/bandage.png");
		break;
	case 44:
		sprite = Sprite::create("gfx/item/can_drink.png");
		break;
	case 45:
		sprite = Sprite::create("gfx/item/candy.png");
		break;
	case 46:
		sprite = Sprite::create("gfx/item/water.png");
		break;
	case 47:
		sprite = Sprite::create("gfx/item/sugar.png");
		break;
	case 60:
		sprite = Sprite::create("gfx/item/greenJelly.png");
		break;
	case 61:
		sprite = Sprite::create("gfx/item/horn_candy.png");
		break;
	case 62:
		sprite = Sprite::create("gfx/item/octoLeg.png");
		break;
	case 63:
		sprite = Sprite::create("gfx/item/stickCookie.png");
		break;
	case 64:
		sprite = Sprite::create("gfx/item/cottonCandy.png");
		break;
	case 65:
		sprite = Sprite::create("gfx/item/macaron.png");
		break;
	case 70:
		sprite = Sprite::create("gfx/item/bubble.png");
		break;
	case 71:
		sprite = Sprite::create("gfx/item/robot.png");
		break;
	case 72:
		sprite = Sprite::create("gfx/item/wallet.png");
		break;
	case 73:
		sprite = Sprite::create("gfx/item/lock.png");
		break;
	case 74:
		sprite = Sprite::create("gfx/item/cardKey.png");
		break;
	case 75:
		sprite = Sprite::create("gfx/item/gasolineBomb.png");
		break;
	default:
		sprite = Sprite::create("gfx/item/default.png");
		break;
	}
	return sprite;
}

std::string SavedGameData::getItemName(int n)
{
	std::string result = "";
	GameItem* item = new GameItem(n);
	result = item->getName();
	return result;
}

void SavedGameData::setNewGameSetting(int level)
{
	floorNum = GameData::MAX_FLOOR;
	//floorNum = 1;
	roomNum = 1;
	this->level = level;
	commuCase = 0;
	commuNum = 0;
	monsterKill = 0;
	tutoEnd = false;
	this->level = level;
	for (int i = 0; i < 3; i++) {
		if (mapData[i] != NULL)
			delete(mapData[i]);
		mapData[i] = NULL;
	}
	gameSetting();
	getPlayer()->setClearPlayer();
}

Player * SavedGameData::getPlayer()
{
	if (player == NULL)
		player = new Player();
	return player;
}

