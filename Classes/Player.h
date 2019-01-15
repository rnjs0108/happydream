#pragma once
#include "ItemBag.h"

class Player //플레이어 정보
{
public:
	static float MAX_HP;
	static float MAX_HUNGER;
private:
	int direct; //1=오른쪽, 2=왼쪽
	ItemBag* bagCell[40]; //가방
	GameItem* equipItem[2];

	int HP; //현재 체력수치
	int hunger; //현재 배고픔수치
	int attack; //공격력
	int attack_p;
	int commuPower; //대화력
	int commuPower_p;
	int depence; //방어력
	int depence_p;
	int hit; //명중률
	int hit_p;
	int eva; //회피율
	int eva_p;
	int devilGage; //전투시 올라가며 공격력 및 방어력 상승에 도움
	int angelGage; //대화시 올라가며 회피력 및 대화력 상승에 도움

public:
	Player();
	~Player();

	int getHP() { return HP; }
	void setHP(int hp) { HP = hp; }
	void addHP(int n);
	void getDamaged(int n) { HP -= n; if (HP < 0) HP = 0; }
	int getHunger() { return hunger; }
	void setHunger(int h) { hunger = h; }
	void addHunger(int n);
	int getDevil() { return devilGage; }
	void addDevil(int n);
	void setDevil(int d) { devilGage = d; }
	int getAngel() { return angelGage; }
	void addAngel(int n);
	void setAngel(int a) { angelGage = a; }
	int getAttack() { return attack; }
	void setAttack(int a) { attack = a; if (attack < 0) attack = 0;}
	int getCommuPower() { return commuPower; }
	void setCommuPower(int c) { commuPower = c; if (commuPower < 0) commuPower = 0; }
	int getDepence() { return depence; }
	void setDepence(int d) { depence = d; if (depence < 0) depence = 0;}
	void addHit(int h) { hit += h; if (hit > 100) hit = 100; else if (hit < 0) hit = 0; }
	int getHit() { return hit; }
	void setHit(int h) { hit = h; }
	void addEva(int e) { eva += e; if (eva > 100) eva = 100; else if (eva < 0) eva = 0; }
	int getEva() { return eva; }
	void setEva(int e) { eva = e; }

	int getAttack_p() { return attack_p; }
	void setAttack_p(int a) { attack_p = a; }
	int getCommuPower_p() { return commuPower_p; }
	void setCommuPower_p(int c) { commuPower_p = c; }
	int getDepence_p() { return depence_p; }
	void setDepence_p(int d) { depence_p = d; }
	void addHit_p(int h) { hit_p += h; }
	int getHit_p() { return hit_p; }
	void setHit_p(int h) { hit_p = h; }
	void addEva_p(int e) { eva_p += e; }
	int getEva_p() { return eva_p; }
	void setEva_p(int e) { eva_p = e; }

	int getTotalAttack() { return attack + attack_p + (devilGage / 20); }
	int getTotalCommuPower() { return commuPower + commuPower_p + (angelGage / 20); }
	int getTotalDepence() { return depence + depence_p; }
	int getTotalHit() { int result = hit + hit_p; if (result > 100) result = 100; return result; }
	int getTotalEva() { int result = eva + eva_p; if (result > 100) result = 100; return result; }

	void setClearPlayer();
	void clearItemBag() { for (int i = 0; i < 40; i++) { delete(bagCell[i]); bagCell[i] = new ItemBag(); } }
	ItemBag* getItemBag(int n) { return bagCell[n]; }
	void SortInventory();
	void setDirect(int n) { direct = n; }
	int getDirect() { return direct; }
	int PlayerItemIndex(); //가지고있는 아이템 종류 갯수 반환
	int someItemIndex(int t); //가지고있는 아이템 종류 갯수 반환
	int someItemBagIndex(int t, int idx); //해당 타입에 순서에 맞는 가방위치 알려줌
	void addItem(int t);
	bool HasItem(int n);
	void deleteItemType(int t);
	GameItem* getEquipItem(int n) { if (n < 2) return equipItem[n]; else return equipItem[0]; }
	void setEquipItem(int t); //가방번호
	void addEquipItem(int type); //타입번호 (디비용)
	void takeOffItem(int n);
	bool isEquipFull() { if (equipItem[0] != 0 && equipItem[1] != 0) return true; else return false; }
	void takeOffItemType(int t);
};