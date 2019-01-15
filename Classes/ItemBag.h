#pragma once
#include "GameItem.h"

class ItemBag //가방 정보
{
private:
	GameItem* item; //등록된 아이템
	int itemNum; //아이템 갯수

public:
	ItemBag();
	~ItemBag();

	GameItem* getItem() { if (item == NULL) return NULL; else return item; }
	int getItemNum() { return itemNum; }
	void firstGetItem(int n);
	void deleteItem();
	void addItem() { itemNum++; };
	void useItem();
	void dropitem(int n);
	void copyBag(ItemBag* ab);
};