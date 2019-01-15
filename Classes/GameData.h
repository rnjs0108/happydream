#pragma once

#include "SavedGameData.h"
#include "Player.h"
#include "MapData.h"

class GameData //전체적인 게임의 데이터
{
public:
	static int MAX_FLOOR;
private:
	int BGMVolume; //sound
	int EffectVolume;
	//기타 랭크 등등 속성

	static GameData* gameData;
	SavedGameData* inGameData;

	SavedGameData* getPlayingGameData() { return inGameData; };
public:
	GameData();
	~GameData();
	int getBGM() { return BGMVolume; }
	void addBGM(int n) { if (BGMVolume > 0) BGMVolume += n; if (BGMVolume <= 0)  BGMVolume = 0; }
	void setBGM(int bgm) { BGMVolume = bgm; }
	int getEffect() { return EffectVolume; }
	void addEffect(int n) { if (EffectVolume > 0) EffectVolume += n; if (EffectVolume <= 0)  EffectVolume = 0; }
	void setEffect(int effect) { EffectVolume = effect; }
	CCSprite* setRoomBGImage();
	
	static MapData* getMapData();
	static Player* getPlayer();
	static SavedGameData* getInGameData();
	static GameData* getGameData();
	static TextManager* getTextManager();
};