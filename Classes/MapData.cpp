#include "MapData.h"
#include "GameData.h"

MapData::MapData(int t, bool mon)
{
	type = t;
	isItemParm = true;
	for (int i = 0; i < 4; i++)
		items[i] = NULL;
	if (mon) {
		monster = new Monster(setMonsterType());
	}
	else {
		monster = NULL;
	}
}

MapData::~MapData()
{
}

bool MapData::HasMonster()
{
	if (monster == NULL)
		return false;
	else
		return true;
}

Monster * MapData::getMonster()
{
	if (HasMonster())
		return monster;
	else
		return nullptr;
}

void MapData::addMonster(int t)
{
	monster = new Monster(t);
}

int MapData::setMonsterType()
{
	int returnType = 0;
	int temp = rand() % 50;
	int nowFloor = GameData::getInGameData()->getFloorNum();
	temp -= nowFloor*2;
	if (temp < -60)
		returnType = 0;
	else if (temp >= -60 && temp < -30)
		returnType = 1;
	else if (temp >= -30 && temp < 10)
		returnType = 2;
	else if (temp >= 10 && temp < 30)
		returnType = 3;
	else if (temp >= 30 && temp < 40)
		returnType = 4;
	else
		returnType = 5;
	if (GameData::getInGameData()->getFloorNum() < 3)
		returnType = 5;
	return returnType;
}

void MapData::setItemList()
{
	int itemNum = 0, ran = 0, n = 0;
	if (HasMonster()) {
		if (getMonster()->getHP() == 0) {
			if(getMonster()->getType() == 9)
				items[0] = new GameItem(60);
			else
				items[0] = new GameItem(60 + getMonster()->getType());
			itemNum = 1;
			n = rand() % 1;
		}
		else if (getMonster()->getWeak() == 0) {
			if (rand() % 100 < 10 + (2 - GameData::getInGameData()->getLevel()) * 5) {
				if (getMonster()->getType() == 9)
					items[0] = new GameItem(70);
				else
					items[0] = new GameItem(70 + getMonster()->getType());
				itemNum = 1;
				n = rand() % 1;
			}
			else
				n = rand() % 2;
		}
	}
	else {
		n = rand() % 3;
	}
	for (int i = itemNum; i <= n + itemNum; i++) {
		ran = rand() % 100;
		if (i < 4) {
			if (ran < 70) //재료
				items[i] = new GameItem(rand() % 12);
			else if (ran >= 70 && ran < 92) //소비
				items[i] = new GameItem(rand() % 8 + 40);
			else if (ran >= 92 && ran < 94) //악세사리
				items[i] = new GameItem(rand() % 13 + 20);
			else //특수
				items[i] = new GameItem(rand() % 6 + 70);
		}
		if (items[0] == NULL)
			isItemParm = false;
	}
}

int MapData::getItemListType(int n)
{
	int i = 0;
	if (items[n] != NULL)
		i = items[n]->getType();
	else
		i = 100;
	return i;
}

void MapData::clearItemList()
{
	for(int i = 0; i < 4; i++ ){
		delete(items[i]);
		items[i] = NULL;
	}
	isItemParm = false;
}
