#pragma once

#include "MapData.h"
#include "Player.h"
#include "cocos2d.h"
#include "TextManager.h"

USING_NS_CC;

class SavedGameData //현재 진행중인 게임 정보
{
private:
	static Player* player; //플레이어 정보
	TextManager* textManager;

	MapData* mapData[3]; //방 정보
	int floorNum; //현재 층의 숫자
	int roomNum; //현재 있는 방의 위치

	int level; //게임 난이도

	int monsterKill; //잡은 몬스터 숫자

	int commuCase; //대화상황
	int commuNum; //대화진행순서

	bool tutoEnd; //튜토리얼 종료
public:
	SavedGameData();
	~SavedGameData();

	int getLevel() { return level; }
	void setLevel(int s) { level = s; }
	int getFloorNum() { return floorNum; }
	void setFloorNum(int n) { floorNum = n; }
	void downTheFloor() { floorNum--; }
	int getRoomNum() { return roomNum; }
	void setRoonNum(int n) { roomNum = n; }
	int getCommuNum() { return commuNum; }
	void setCommuNum(int n) { commuNum = n; }
	int getCommuCase() { return commuCase; }
	void setCommuCase(int n) { commuCase = n; }
	bool getTutoEnd() { return tutoEnd; }
	void setTutoEnd(bool b) { tutoEnd = b; }
	void setMonsterKill(int m) { monsterKill = m; }
	void addMonsterKill() { monsterKill++; }
	int getMonsterKill() { return monsterKill; }
	void nextText() { if(getTextManager()->getTextList()->lastNodeNum() > commuNum ) commuNum++; }
	void previousText() { if(commuNum > 0) commuNum--; }
	MapData* getMapData() { return mapData[roomNum]; }
	MapData* getMapDataNumber(int n) { return mapData[n]; }
	void gameSetting();
	CCSprite* getItemImage(int n);
	std::string getItemName(int n);
	void setNewGameSetting(int level);

	static Player* getPlayer();
	TextManager* getTextManager() { return textManager; }
};