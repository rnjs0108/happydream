#pragma once
#include "cocos2d.h"
#include "Monster.h"
#include "GameItem.h"

class MapData //맵정보
{
private:
	Monster* monster;
	int type; //방의 구조 타입
	bool isItemParm;
	GameItem* items[4];
public:
	MapData(int t, bool mon);
	~MapData();
	
	bool HasMonster();
	Monster* getMonster();
	void addMonster(int t);
	void deleteMonster() { if (monster != NULL) { delete(monster); monster = NULL; } }
	int getType() { return type; }
	void setType(int t) { type = t; };
	int setMonsterType();
	bool getIsItemParm() { return isItemParm; }
	void setIsItemParm(bool b) { isItemParm = b; }
	void setItemList();
	int getItemListType(int n);
	void clearItemList();
	void createMonster() { if (monster == NULL) monster = new Monster(0); }
};