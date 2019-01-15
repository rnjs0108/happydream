#include "GameItem.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")

GameItem::GameItem(int t)
{
	type = t;
	pointExp = "";
	switch (type) {
	case 0:
		name = "본드";
		exp = "무언가 붙이는데 쓸 수 있을 것 같다.";
		canUse = false;
		break;
	case 1:
		name = "동전";
		exp = "알수없는 글씨가 적힌 화폐이다.";
		canUse = false;
		break;
	case 2:
		name = "헝겊조각";
		exp = "부드러운 재질로 되어 있다.";
		canUse = false;
		break;
	case 3:
		name = "나무판자";
		exp = "꽤 단단한 나무판자이다.";
		canUse = false;
		break;
	case 4:
		name = "알코올";
		exp = "소독용 알코올이다.";
		canUse = false;
		break;
	case 5:
		name = "비누";
		exp = "누군가 쓰다가 남은 비누이다.";
		canUse = false;
		break;
	case 6:
		name = "테이프";
		exp = "얼마 남지않은 테이프뭉치이다.";
		canUse = false;
		break;
	case 7:
		name = "스테이플러";
		exp = "종이를 찝는데 필요한 도구이다.";
		canUse = false;
		break;
	case 8:
		name = "고무줄";
		exp = "생각보다 질긴 고무줄이다.";
		canUse = false;
		break;
	case 9:
		name = "건전지";
		exp = "힘 세고 오래 간다는 건전지이다.";
		canUse = false;
		break;
	case 10:
		name = "로보트";
		exp = "전원을 눌러도 작동하지 않는다.";
		canUse = false;
		break;
	case 11:
		name = "라이터";
		exp = "가스가 얼마 남아있지 않다.";
		canUse = false;
		break;
	case 20:
		name = "메스";
		exp = "수술용 도구이다.";
		pointExp = "공격력 +6 명중률 +5";
		canUse = true;
		break;
	case 21:
		name = "나이프";
		exp = "꽤나 위협적인 무기이다.";
		pointExp = "공격력 +3 명중률 +3";
		canUse = true;
		break;
	case 22:
		name = "하트 열쇠고리";
		exp = "가방에 걸고 다니고 싶다.";
		pointExp = "친근감 +5 방어력 +2";
		canUse = true;
		break;
	case 23:
		name = "곰인형";
		exp = "때가 조금 묻어있다.";
		pointExp = "참을성 +4";
		canUse = true;
		break;
	case 24:
		name = "대걸레";
		exp = "흔한 청소용 도구이다.";
		pointExp = "공격력 +2 방어력 +2";
		canUse = true;
		break;
	case 25:
		name = "맥가이버칼";
		exp = "만능 다용도 칼이다.";
		pointExp = "공격력 +1";
		canUse = true;
		break;
	case 26:
		name = "토끼인형";
		exp = "내 친구이다.";
		pointExp = "선함 +3";
		canUse = true;
		break;
	case 27:
		name = "클로버 열쇠고리";
		exp = "행운이 찾아올 것 같다.";
		pointExp = "행운 +6 회피율 +3";
		canUse = true;
		break;
	case 28:
		name = "동화책";
		exp = "내가 좋아하는 이야기이다.";
		pointExp = "지식 +7 방어력 +4";
		canUse = true;
		break;
	case 29:
		name = "손목보호대";
		exp = "나름 꼼꼼하게 만들어진 보호대이다.";
		pointExp = "방어력 +6 회피율 +4";
		canUse = true;
		break;
	case 30:
		name = "개조 스테이플러";
		exp = "매우 위협적이나 맞추기는 어려워보인다.";
		pointExp = "공격력 +12 명중률 -10";
		canUse = true;
		break;
	case 31:
		name = "천장갑";
		exp = "손을 보호할 수 있다.";
		pointExp = "방어력 +3 회피율 +2";
		canUse = true;
		break;
	case 32:
		name = "창";
		exp = "공방에 모두 유용한 무기이다.";
		pointExp = "공격력 +6 방어력 +4";
		canUse = true;
		break;
	case 40:
		name = "과자";
		exp = "엄청 눅눅해 보인다.";
		pointExp = "배부름 +2";
		canUse = true;
		break;
	case 41:
		name = "소보루빵";
		exp = "유통기한이 어딨는지 모르겠다.";
		pointExp = "배부름 +4";
		canUse = true;
		break;
	case 42:
		name = "구급상자";
		exp = "응급상황시 유용해보인다.";
		pointExp = "체력 +30";
		canUse = true;
		break;
	case 43:
		name = "붕대";
		exp = "조금 더럽지만 쓸만해 보인다.";
		pointExp = "회복 +15";
		canUse = true;
		break;
	case 44:
		name = "캔음료";
		exp = "제일 싫어하는 맛이다.";
		pointExp = "배부름 +3 회복 +8";
		canUse = true;
		break;
	case 45:
		name = "사탕";
		exp = "홍삼맛이다.";
		pointExp = "배부름 +1";
		canUse = true;
		break;
	case 46:
		name = "물병";
		exp = "잘 밀봉된 물병이다.";
		pointExp = "배부름 +2 회복 +5";
		canUse = true;
		break;
	case 47:
		name = "설탕";
		exp = "그냥 먹으면 너무 달다.";
		pointExp = "배부름 +1";
		canUse = true;
		break;
	case 60:
		name = "초록 젤리";
		exp = "달콤한 냄새가 나는 젤리이다.";
		pointExp = "배부름 +3";
		canUse = true;
		break;
	case 61:
		name = "뿔모양 사탕";
		exp = "먹으면 힘이 날 것 같다.";
		pointExp = "회복 +5 배부름 +1";
		canUse = true;
		break;
	case 62:
		name = "문어다리";
		exp = "고소한 냄새가 난다.";
		pointExp = "회피율 +1 배부름 +1";
		canUse = true;
		break;
	case 63:
		name = "막대과자";
		exp = "안에는 초콜릿이 가득한 과자이다.";
		pointExp = "명중률 +1 배부름 +1";
		canUse = true;
		break;
	case 64:
		name = "솜사탕";
		exp = "구름같은 달콤한 솜사탕이다.";
		pointExp = "공격력 +1 배부름 +1";
		canUse = true;
		break;
	case 65:
		name = "마카롱";
		exp = "알록달록 이쁜 마카롱이다.";
		pointExp = "공격력 +1 방어력 +1\n배부름 +1";
		canUse = true;
		break;
	case 70:
		name = "비눗방울";
		exp = "슬라임이 좋아할 것 같다.";
		canUse = false;
		break;
	case 71:
		name = "로보트";
		exp = "클롭이 좋아하는 장난감이다.";
		canUse = false;
		break;
	case 72:
		name = "지갑";
		exp = "더블옥토가 잃어버린 지갑같다.";
		canUse = false;
		break;
	case 73:
		name = "자물쇠";
		exp = "너르가 찾고있는 자물쇠이다.";
		canUse = false;
		break;
	case 74:
		name = "카드키";
		exp = "딕토의 집 카드이다.";
		canUse = false;
		break;
	case 75:
		name = "화염병";
		exp = "세큐리가 좋아하는 불꽃놀이다.";
		canUse = false;
		break;
	default:
		std::ostringstream ostr;
		ostr.str(""); ostr.clear();
		ostr << "타입: ";
		ostr << type;
		name = ostr.str();
		exp = "아직 안만듬";
		canUse = false;
		break;
	}
}

GameItem::~GameItem()
{
}

void GameItem::use()
{
	switch (type) {
	case 40: //과자
		GameData::getPlayer()->addHunger(2);
		break;
	case 41: //소보루빵
		GameData::getPlayer()->addHunger(4);
		break;
	case 42: //구급상자
		GameData::getPlayer()->addHP(30);
		break;
	case 43: //붕대
		GameData::getPlayer()->addHP(15);
		break;
	case 44: //캔음료
		GameData::getPlayer()->addHunger(3);
		GameData::getPlayer()->addHP(8);
		break;
	case 45: //사탕
		GameData::getPlayer()->addHunger(1);
		break;
	case 46: //물병
		GameData::getPlayer()->addHunger(2);
		GameData::getPlayer()->addHP(5);
		break;
	case 47: //설탕
		GameData::getPlayer()->addHunger(1);
		break;
	case 60: //초록 젤리
		GameData::getPlayer()->addHunger(3);
		GameData::getPlayer()->addDevil(1);
		break;
	case 61: //뿔모양 사탕
		GameData::getPlayer()->addHP(5);
		GameData::getPlayer()->addDevil(1);
		break;
	case 62: //문어다리
		GameData::getPlayer()->addEva(1);
		GameData::getPlayer()->addHunger(1);
		GameData::getPlayer()->addDevil(2);
		break;
	case 63: //막대사탕
		GameData::getPlayer()->addHit(1);
		GameData::getPlayer()->addHunger(1);
		GameData::getPlayer()->addDevil(2);
		break;
	case 64: //솜사탕
		GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack()+1);
		GameData::getPlayer()->addHunger(1);
		GameData::getPlayer()->addDevil(3);
		break;
	case 65: //마카롱
		GameData::getPlayer()->setAttack(GameData::getPlayer()->getAttack() + 1);
		GameData::getPlayer()->setDepence(GameData::getPlayer()->getDepence() + 1);
		GameData::getPlayer()->addHunger(1);
		GameData::getPlayer()->addDevil(4);
		break;
	default:
		break;
	}
}

void GameItem::equip()
{
	switch (type) {
	case 20: //메스
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 6);
		GameData::getPlayer()->addHit_p(5);
		break;
	case 21: //나이프
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 3);
		GameData::getPlayer()->addHit_p(3);
		break;
	case 22: //하트 열쇠고리
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() + 5);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 2);
		break;
	case 23: //곰인형
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() + 4);
		break;
	case 24: //대걸레
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 2);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 2);
		break;
	case 25: //맥가이버칼
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 1);
		break;
	case 26: //토끼인형
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() + 3);
		break;
	case 27: //클로버 열쇠고리
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() + 6);
		GameData::getPlayer()->addEva_p(3);
		break;
	case 28: //동화책
		GameData::getPlayer()->setCommuPower_p(GameData::getPlayer()->getCommuPower_p() + 7);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 4);
		break;
	case 29: //손목보호대
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 6);
		GameData::getPlayer()->addEva_p(4);
		break;
	case 30: //개조 스테이플러
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 12);
		GameData::getPlayer()->addHit_p(-10);
		break;
	case 31: //천장갑
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 3);
		GameData::getPlayer()->addEva_p(2);
		break;
	case 32: //창
		GameData::getPlayer()->setAttack_p(GameData::getPlayer()->getAttack_p() + 6);
		GameData::getPlayer()->setDepence_p(GameData::getPlayer()->getDepence_p() + 4);
		break;
	default:
		break;
	}
}
