#include "Player.h"
#include "cocos2d.h"
#include "GameData.h"

float Player::MAX_HP = 100.0f;
float Player::MAX_HUNGER = 20.0f;
Player::Player()
{
	for (int i = 0; i < 40; i++) {
		bagCell[i] = new ItemBag();
	}
	setClearPlayer();	
}

Player::~Player()
{
	for (int i = 0; i < 40; i++) {
		free(bagCell[i]);
		bagCell[i] = NULL;
	}
}

void Player::addHP(int n)
{
	int num = n;
	if (num > 0) {
		HP += num;
		if (HP > MAX_HP)
			HP = MAX_HP;
	}
	else {
		HP += num;
		if (HP < 0)
			HP = 0;
	}
}

void Player::addHunger(int n)
{
	int num = n;
	if (num > 0) {
		hunger += num;
		if (hunger > MAX_HUNGER)
			hunger = MAX_HUNGER;
	}
	else {
		while(num < 0 && hunger > 0){
			hunger--;
			num++;
		}
		addHP(num*2);
	}
}

void Player::addDevil(int n) //전투 승리시
{
	int num = n;
	if (num > 0) {
		while (angelGage > 0 && num > 0) {
			angelGage--;
			num--;
		}
		devilGage += num;
		if (devilGage > 100)
			devilGage = 100;
	}
	else {
		for (num; num < 0 && devilGage > 0; num++) {
			devilGage--;
		}
		angelGage -= num;
	}
}

void Player::addAngel(int n) //대화 성공시 n만큼 더해줌
{
	int num = n;
	if (num > 0) {
		while (devilGage > 0 && num > 0) {
			devilGage--;
			num--;
		}
		angelGage += num;
		if (angelGage > 100)
			angelGage = 100;
	}
	else {
		for (num; num < 0 && angelGage > 0; num++) {
			angelGage--;
		}
		devilGage -= num;
	}
}

void Player::setClearPlayer()
{
	direct = 1;
	HP = (int)MAX_HP;
	hunger = (int)MAX_HUNGER;
	attack = 2 + (2 - GameData::getInGameData()->getLevel()) * 2;
	commuPower = 0;
	depence = (2 - GameData::getInGameData()->getLevel()) * 2;
	hit = (2 - GameData::getInGameData()->getLevel()) * 5;
	eva = (2 - GameData::getInGameData()->getLevel()) * 5;
	attack_p = 0;
	commuPower_p = 0;
	depence_p = 0;
	hit_p = 0;
	eva_p = 0;
	devilGage = 0;
	angelGage = 0;
	for (int i = 0; i < 40; i++){
		if (bagCell[i] != NULL)
			delete(bagCell[i]);
		bagCell[i] = new ItemBag();
	}
	equipItem[0] = NULL;
	equipItem[1] = NULL;
	addItem(40);
}

void Player::SortInventory()
{
	int j = 0;
	for (int i = 1; i < 40; i++) {
		if (bagCell[i - 1]->getItemNum() == 0 && bagCell[i]->getItemNum() != 0) { //칸이 비어있으면	
			bagCell[i - 1]->copyBag(bagCell[i]);
			bagCell[i]->deleteItem();
		}
	}
}

int Player::PlayerItemIndex()
{
	int num = 0;
	for (int i = 0; i < 40; i++)
		if (bagCell[i]->getItemNum() == 0) break; else num++;
	return num;
}

int Player::someItemIndex(int t) //아이템 갯수 반환
{
	int num = 0;
	if(t==0){
	for (int i = 0; i < 40; i++)
		if (bagCell[i]->getItemNum() == 0) break; else num++;
	}
	else if (t == 1) { //장비아이템만 반환
		for (int i = 0; i < 40; i++)
			if (bagCell[i]->getItemNum() == 0)
				break;
			else{
				if(bagCell[i]->getItem()->getType() >= 20 && bagCell[i]->getItem()->getType() < 40)
					num++;
			}
	}
	else if (t == 2) { //소비아이템만 반환
		for (int i = 0; i < 40; i++)
			if (bagCell[i]->getItemNum() == 0)
				break;
			else {
				if (bagCell[i]->getItem()->getType() >= 40 && bagCell[i]->getItem()->getType() < 70)
					num++;
			}
	}
	else if (t == 3) { //장비 소비 이외 모든 재료아이템 반환
		for (int i = 0; i < 40; i++)
			if (bagCell[i]->getItemNum() == 0)
				break;
			else {
				if (bagCell[i]->getItem()->getType() < 20 || bagCell[i]->getItem()->getType() >= 70)
					num++;
			}
	}
	return num;
}

int Player::someItemBagIndex(int t, int idx)
{
	int i = 0; //결과값 가방위치
	int num = 0; //해당 타입아이템 순서
	if (t == 0)
		i = idx;
	else if (t == 1) { //장비아이템 순서
		for (i = 0; i < 40; i++){
			if (bagCell[i]->getItemNum() == 0)
				break;
			else {
				if (bagCell[i]->getItem()->getType() >= 20 && bagCell[i]->getItem()->getType() < 40)
					if (num == idx)
						break;
					else
						num++;
			}
		}
	}
	else if (t == 2) { //소비아이템만 반환
		for (i = 0; i < 40; i++) {
			if (bagCell[i]->getItemNum() == 0)
				break;
			else {
				if (bagCell[i]->getItem()->getType() >= 40 && bagCell[i]->getItem()->getType() < 70)
					if (num == idx)
						break;
					else
						num++;
			}
		}
	}
	else if (t == 3) { //장비 소비 이외 모든 재료아이템 반환
		for (i = 0; i < 40; i++) {
			if (bagCell[i]->getItemNum() == 0)
				break;
			else {
				if (bagCell[i]->getItem()->getType() < 20 || bagCell[i]->getItem()->getType() >= 70)
					if (num == idx)
						break;
					else
						num++;
			}
		}
	}
	return i;
}

void Player::addItem(int t)
{
	int i = 0;
	while (i < 40) {
		if(bagCell[i]->getItemNum() != 0) //아이템칸이 비어있지 않고
			if (bagCell[i]->getItem()->getType() == t) { //아이템 종류가 일치함
				bagCell[i]->addItem();
				i = 50;
			}
			i++;
		}
	if (i == 40) { //같은 아이템이 없음
		i = 0;
		while (i < 40 && bagCell[i]->getItemNum() != 0) { //빈칸을 찾음
			i++;
		}
		if (i < 40) { //빈칸이 있음
			bagCell[i]->firstGetItem(t);
		}
		else { //빈칸이 없음
		}
	}
	SortInventory();
}

bool Player::HasItem(int n)
{
	int value = 0;
	bool result = false;
	for (int i = 0; i < PlayerItemIndex(); i++) {
		if (getItemBag(i)->getItem()->getType() == n)
			value++;
	}
	if (value > 0)
		result = true;
	else
		result = false;
	return result;
}

void Player::deleteItemType(int t)
{
	for (int i = 0; i < PlayerItemIndex(); i++) {
		if (getItemBag(i)->getItem()->getType() == t)
			getItemBag(i)->dropitem(1);
	}
}

void Player::setEquipItem(int t) //아이템 장착(인덱스 번호)
{
	int num = 0;
	if (equipItem[0] != NULL) //순서대로 장착
		num = 1;
	equipItem[num] = getItemBag(t)->getItem(); //장착
	 //해당 타입에 맞는 능력치 상승
	equipItem[num]->equip();
	//해당 아이템 삭제
	getItemBag(t)->dropitem(1);
}

void Player::addEquipItem(int type)
{
	int num = 0;
	if (equipItem[0] != NULL) //순서대로 장착
		num = 1;
	equipItem[num] = new GameItem(type); //장착
	//해당 타입에 맞는 능력치 상승
	equipItem[num]->equip();
}

void Player::takeOffItem(int n) //아이템 해제(해당 장착위치)
{
	takeOffItemType(equipItem[n]->getType());
	addItem(equipItem[n]->getType()); //아이템 다시 추가
	equipItem[n] = NULL; //장착해제
}

void Player::takeOffItemType(int t)
{
	switch (t) {
	case 20: //메스
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 6);
		GameData::getPlayer()->addHit_p(-5);
		break;
	case 21: //나이프
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 3);
		GameData::getPlayer()->addHit_p(-3);
		break;
	case 22: //하트 열쇠고리
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() - 5);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 2);
		break;
	case 23: //곰인형
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() - 4);
		break;
	case 24: //대걸레
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 2);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 2);
		break;
	case 25: //맥가이버칼
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 1);
		break;
	case 26: //토끼인형
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() - 3);
		break;
	case 27: //클로버 열쇠고리
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() - 5);
		GameData::getPlayer()->addEva_p(-3);
		break;
	case 28: //동화책
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() - 7);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 3);
		break;
	case 29: //손목보호대
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 6);
		GameData::getPlayer()->addEva_p(-4);
		break;
	case 30: //개조 스테이플러
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 12);
		GameData::getPlayer()->addHit_p(10);
		break;
	case 31: //천장갑
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 3);
		GameData::getPlayer()->addEva_p(-2);
		break;
	case 32: //창
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() - 6);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() - 4);
		break;
	default:
		break;
	}
}
