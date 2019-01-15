#include "ItemBag.h"
#include "GameData.h"

ItemBag::ItemBag()
{
	item = NULL;
	itemNum = 0;
}

ItemBag::~ItemBag()
{
}

void ItemBag::firstGetItem(int n)
{
	item = new GameItem(n);
	itemNum = 1;
}

void ItemBag::deleteItem()
{
	//GameItem* temp = item;
	item = NULL;
	//delete temp;
	itemNum = 0;
}

void ItemBag::useItem()
{
	item->use();
	if (itemNum > 1)
		itemNum--;
	else {
		deleteItem();
	}
	GameData::getPlayer()->SortInventory();
}

void ItemBag::dropitem(int n)
{
	if (itemNum > n)
		itemNum -= n;
	else {
		deleteItem();
	}
	GameData::getPlayer()->SortInventory();
}

void ItemBag::copyBag(ItemBag * ab)
{
	item = ab->getItem();
	itemNum = ab->getItemNum();
}
