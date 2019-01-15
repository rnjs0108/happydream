#include "Monster.h"

Monster::Monster(int t)
{
	settingMonster(t);
	HP = MAXHP;
	weak = MAXWEAK;
}

Monster::~Monster()
{
}

void Monster::settingMonster(int t)
{
	type = t;
	switch (type) {
	case 0:
		MAXHP = 20;
		MAXWEAK = 10;
		damage = 5;
		depence = 6;
		luck = 2;
		break;
	case 1:
		MAXHP = 30;
		MAXWEAK = 14;
		damage = 6;
		depence = 4;
		luck = 3;
		break;
	case 2:
		MAXHP = 40;
		MAXWEAK = 18;
		damage = 9;
		depence = 6;
		luck = 4;
		break;
	case 3:
		MAXHP = 35;
		MAXWEAK = 22;
		damage = 12;
		depence = 3;
		luck = 5;
		break;
	case 4:
		MAXHP = 55;
		MAXWEAK = 30;
		damage = 12;
		depence = 10;
		luck = 5;
		break;
	case 5:
		MAXHP = 50;
		MAXWEAK = 35;
		damage = 16;
		depence = 14;
		luck = 5;
		break;
	case 9:
		MAXHP = 10;
		MAXWEAK = 5;
		damage = 1;
		depence = 2;
		luck = 2;
		break;
	default:
		MAXHP = 20;
		MAXWEAK = 10;
		damage = 5;
		depence = 8;
		luck = 5;
		break;
	}
}
