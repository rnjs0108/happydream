#pragma once
#include<iostream>

class GameItem //아이템 정보
{
private:
	std::string name; //이름
	std::string exp; //상세정보
	std::string pointExp; //능력치
	int type; //아이템의 타입
	bool canUse;
public:
	GameItem(int t);
	~GameItem();

	int getType() { return type; }
	bool getCanUse() { return canUse; }
	std::string getName() { return name; }
	std::string getExp() { return exp; }
	std::string getPointExp() { return pointExp; }

	void use();
	void equip();

	static GameItem* itemNumbergetItem(int t) { return new GameItem(t); }
	static std::string itemNumbergetName(int t) { GameItem* item = new GameItem(t); return item->getName(); }
	static std::string itemNumbergetExp(int t) { GameItem* item = new GameItem(t); return item->getExp(); }
	static std::string itemNumbergetPointExp(int t) { GameItem* item = new GameItem(t); return item->getPointExp(); }
};