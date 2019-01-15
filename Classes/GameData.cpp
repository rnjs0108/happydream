#include "GameData.h"
#pragma execution_character_set("UTF-8")

GameData* GameData::gameData = NULL;
int GameData::MAX_FLOOR = 50;

GameData::GameData()
{
	BGMVolume = 1;
	EffectVolume = 1;
	inGameData = new SavedGameData();
}

GameData::~GameData()
{
}

CCSprite * GameData::setRoomBGImage()
{
	CCSprite* roomBG = CCSprite::create("gfx/backGround/room6.png");
	int i = GameData::getInGameData()->getMapData()->getType();
	switch (i) {
	case 0:
		roomBG->setTexture("gfx/backGround/room0.png");
		break;
	case 1:
		roomBG->setTexture("gfx/backGround/room1.png");
		break;
	case 2:
		roomBG->setTexture("gfx/backGround/room2.png");
		break;
	case 3:
		roomBG->setTexture("gfx/backGround/room3.png");
		break;
	case 4:
		roomBG->setTexture("gfx/backGround/room4.png");
		break;
	case 5:
		roomBG->setTexture("gfx/backGround/room5.png");
		break;
	case 6:
		roomBG->setTexture("gfx/backGround/room6.png");
		break;
	case 7:
		roomBG->setTexture("gfx/backGround/room7.png");
		break;
	case 8:
		roomBG->setTexture("gfx/backGround/room6.png");
		break;
	case 9:
		roomBG->setTexture("gfx/backGround/room7.png");
		break;
	case 10:
		roomBG->setTexture("gfx/backGround/room6.png");
		break;
	}
	return roomBG;
}

MapData * GameData::getMapData()
{
	return GameData::getGameData()->getInGameData()->getMapData();
}

Player * GameData::getPlayer()
{
	return GameData::getGameData()->getPlayingGameData()->getPlayer();
}

SavedGameData * GameData::getInGameData()
{
	return GameData::getGameData()->getPlayingGameData();
}

GameData * GameData::getGameData()
{
	if (gameData == NULL) {
		log("게임데이터 생성");
		gameData = new GameData();
	}
	return gameData;
}

TextManager * GameData::getTextManager()
{
	return GameData::getGameData()->getInGameData()->getTextManager();
}
