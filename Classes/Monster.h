#pragma once
class Monster //몬스터 정보
{
private:
	int MAXHP;
	int MAXWEAK;
	int type;
	int HP;
	int weak;
	int damage;
	int depence;
	int luck;
public:
	Monster(int t);
	~Monster();

	int getType() { return type; }
	int getMAXHP() { return MAXHP; }
	int getMAXWEAK() { return MAXWEAK; }
	void setHP(int h) { HP = h; }
	int getHP() { return HP; }
	void setWeak(int w) { weak = w; }
	int getWeak() { return weak; }
	void setAttack(int d) { damage = d;}
	int getAttack() { return damage; }
	void setDepence(int d) { depence = d; }
	int getDepence() { return depence; }
	void getDamaged(int d) { if(HP >= d) HP -= d; else HP = 0; }
	void getWeakDamaged(int d) { if (weak >= d) weak -= d; else weak = 0; }
	void settingMonster(int t);
};