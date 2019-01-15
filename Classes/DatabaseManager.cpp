#include "DatabaseManager.h"
#include <string>
#include "DevConf.h"
#include "GameData.h"

#define DB_FILE_NAME "db.sqlite"

//DatabaseManager 객체
static DatabaseManager *_sharedSqlite = NULL;

//생성자
DatabaseManager::DatabaseManager()
{
}

//소멸자
DatabaseManager::~DatabaseManager()
{
	//_sharedSqlite가 있으면
	if (_sharedSqlite != NULL) {
		_sharedSqlite->closeDB();
		_sharedSqlite = NULL;
	}
}

//DatabaseManager 객체를 반환한다.
DatabaseManager* DatabaseManager::getInstance() {
	//_sharedSqlite가 없으면
	if (!_sharedSqlite) {
		_sharedSqlite = new DatabaseManager;
		_sharedSqlite->openDB();
	}
	return _sharedSqlite;
}

//데이터베이스를 오픈한다.
bool DatabaseManager::openDB() {
	//데이터베이스의 path를 가져온다.
	std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;
	//데이터베이스의 path를 출력한다.
	log("path : %s", path.c_str());

	//데이터베이스를 open한다.
	_result = sqlite3_open(path.c_str(), &_sqlite);

	if (_result != SQLITE_OK) {
		log("failed to create db");
		return false;
	}
	return true;
}



//데이터베이스를 닫는다.
void DatabaseManager::closeDB() {
	sqlite3_close(_sqlite);
}

//테이블 생성
void DatabaseManager::createDB() {
	if (DB_INIT) {        //디비 초기화를 위한 개발자 변수값
		std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;
		//데이터베이스의 파일이 열려있으면 삭제가 안되므로 데이터베이스를 닫아준다.
		closeDB();
		//db파일을 삭제
		remove(path.c_str());
		//데이터베이스를 닫았으므로 다시 열어준다.
		openDB();
	}

	std::string query = "create table if not exists HD_DATA(";
	query += "num integer primary key, value integer";
	query += ")";
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);
	if (_result == SQLITE_OK) {
		log("createDataDB() SUCCESS");

	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	query = "create table if not exists HD_ITEM(";
	query += "type integer primary key, value integer";
	query += ")";
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);
	if (_result == SQLITE_OK) {
		log("createItemDB() SUCCESS");

	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	query = "create table if not exists HD_MONSTER(";
	query += "roomNum integer primary key, type integer, HP integer, week integer, attack integer, depence integer";
	query += ")";
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);
	if (_result == SQLITE_OK) {
		log("createMonsterDB() SUCCESS");

	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::loadAllData()
{
	loadDataToDB();
	loadItemList();
	loadMonster();
}

void DatabaseManager::loadSettingData()
{
	std::string query = "select * from HD_DATA";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);
	GameData::getPlayer()->setClearPlayer();
	if (_result == SQLITE_OK) {
		log("loadSettingData() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			switch (sqlite3_column_int(stmt, 0)) {
			case 0:
				GameData::getGameData()->setBGM(sqlite3_column_int(stmt, 1));
				break;
			case 1:
				GameData::getGameData()->setEffect(sqlite3_column_int(stmt, 1));
				break;
			}
		}
	}
	else {
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	sqlite3_finalize(stmt);
}

void DatabaseManager::loadDataToDB()
{
	std::string query = "select * from HD_DATA";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);
	GameData::getPlayer()->setClearPlayer();
	if (_result == SQLITE_OK) {
		log("loadDataDB() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			switch (sqlite3_column_int(stmt, 0)) {
			case 0:
				GameData::getGameData()->setBGM(sqlite3_column_int(stmt, 1));
				break;
			case 1:
				GameData::getGameData()->setEffect(sqlite3_column_int(stmt, 1));
				break;
			case 10:
				GameData::getInGameData()->setFloorNum(sqlite3_column_int(stmt, 1));
				break;
			case 11:
				GameData::getInGameData()->setRoonNum(sqlite3_column_int(stmt, 1));
				break;
			case 12:
				GameData::getInGameData()->setLevel(sqlite3_column_int(stmt, 1));
				break;
			case 13:
				GameData::getInGameData()->setMonsterKill(sqlite3_column_int(stmt, 1));
				break;
			case 20:
				if (sqlite3_column_int(stmt, 1) == 0)
						GameData::getInGameData()->getMapDataNumber(0)->createMonster();
				break;
			case 21:
				GameData::getInGameData()->getMapDataNumber(0)->setType(sqlite3_column_int(stmt, 1));
				break;
			case 22:
				GameData::getInGameData()->getMapDataNumber(0)->setIsItemParm(sqlite3_column_int(stmt, 1) == 0 ? true : false);
				break;
			case 23:
				if (sqlite3_column_int(stmt, 1) == 0)
					GameData::getInGameData()->getMapDataNumber(1)->createMonster();
				break;
			case 24:
				GameData::getInGameData()->getMapDataNumber(1)->setType(sqlite3_column_int(stmt, 1));
				break;
			case 25:
				GameData::getInGameData()->getMapDataNumber(1)->setIsItemParm(sqlite3_column_int(stmt, 1) == 0 ? true : false);
				break;
			case 26:
				if (sqlite3_column_int(stmt, 1) == 0)
					GameData::getInGameData()->getMapDataNumber(2)->createMonster();
				break;
			case 27:
				GameData::getInGameData()->getMapDataNumber(2)->setType(sqlite3_column_int(stmt, 1));
				break;
			case 28:
				GameData::getInGameData()->getMapDataNumber(2)->setIsItemParm(sqlite3_column_int(stmt, 1) == 0 ? true : false);
				break;
			case 40:
				GameData::getPlayer()->setHP(sqlite3_column_int(stmt, 1));
				break;
			case 41:
				GameData::getPlayer()->setHunger(sqlite3_column_int(stmt, 1));
				break;
			case 42:
				GameData::getPlayer()->setAttack(sqlite3_column_int(stmt, 1));
				break;
			case 43:
				GameData::getPlayer()->setCommuPower(sqlite3_column_int(stmt, 1));
				break;
			case 44:
				GameData::getPlayer()->setDepence(sqlite3_column_int(stmt, 1));
				break;
			case 45:
				GameData::getPlayer()->setHit(sqlite3_column_int(stmt, 1));
				break;
			case 46:
				GameData::getPlayer()->setEva(sqlite3_column_int(stmt, 1));
				break;
			case 47:
				GameData::getPlayer()->setDevil(sqlite3_column_int(stmt, 1));
				break;
			case 48:
				GameData::getPlayer()->setAngel(sqlite3_column_int(stmt, 1));
				break;
			case 49:
				if(sqlite3_column_int(stmt, 1) != 0)
					GameData::getPlayer()->addEquipItem(sqlite3_column_int(stmt, 1));
				break;
			case 50:
				if (sqlite3_column_int(stmt, 1) != 0)
					GameData::getPlayer()->addEquipItem(sqlite3_column_int(stmt, 1));
				break;
			}
		}
	}
	else {
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	sqlite3_finalize(stmt);
}

void DatabaseManager::loadItemList()
{
	std::string query = "select * from HD_ITEM";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);
	GameData::getPlayer()->clearItemBag();
	if (_result == SQLITE_OK) {
		log("loadItemDB() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			for(int i=0;i<sqlite3_column_int(stmt, 1);i++)
				GameData::getPlayer()->addItem(sqlite3_column_int(stmt, 0));
		}
		log("itemValue : %d", GameData::getPlayer()->getItemBag(0)->getItemNum());
		log("itemValue : %d", GameData::getPlayer()->getItemBag(1)->getItemNum());
	}
	else {
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	sqlite3_finalize(stmt);
}

void DatabaseManager::loadMonster()
{
	std::string query = "select * from HD_MONSTER";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);
	if (_result == SQLITE_OK) {
		log("loadMonsterDB() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			if (sqlite3_column_int(stmt, 1) == 20) {
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->deleteMonster();
			}
			else {
				if (!GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->HasMonster())
						GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->createMonster();
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->getMonster()->settingMonster(sqlite3_column_int(stmt, 1));
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->getMonster()->setHP(sqlite3_column_int(stmt, 2));
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->getMonster()->setWeak(sqlite3_column_int(stmt, 3));
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->getMonster()->setAttack(sqlite3_column_int(stmt, 4));
				GameData::getInGameData()->getMapDataNumber(sqlite3_column_int(stmt, 0))->getMonster()->setDepence(sqlite3_column_int(stmt, 5));
			}
		}
	}
	else {
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	sqlite3_finalize(stmt);
}

void DatabaseManager::saveAllData()
{
	saveDataToDB();
	saveItemList();
	saveMonster();
}

void DatabaseManager::updateSettingData() //사운드 저장
{
	saveSettingData();
	std::ostringstream text;
	text.str("");
	text.clear();
	text << "update HD_DATA set value=";
	text << GameData::getGameData()->getBGM();
	text << " where num=0";
	std::string query = text.str();
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("saveSettingData()_1 SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);

	text.str("");
	text.clear();
	text << "update HD_DATA set value=";
	text << GameData::getGameData()->getEffect();
	text << " where num=1";
	query = text.str();
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("saveSettingData()_2 SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::saveSettingData()
{
	std::ostringstream text;
	text.str("");
	text.clear();
	text << "insert into HD_DATA values (0, ";
	text << GameData::getGameData()->getBGM();
	text << "), (1,";
	text << GameData::getGameData()->getEffect();
	text << ")";
	std::string query = text.str();
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("insertDataDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::saveDataToDB()
{
	/*
	std::string dd;
	dd.reserve(200);
	dd += "dasf";
	dd += "Ffff";
	*/


	deleteDataToDB();
	std::ostringstream text;
	text.str("");
	text.clear();
	text << "insert into HD_DATA values (0, ";
	text << GameData::getGameData()->getBGM();
	text << "), (1,";
	text << GameData::getGameData()->getEffect();
	text << "), (10,";
	text << GameData::getInGameData()->getFloorNum();
	text << "), (11,";
	text << GameData::getInGameData()->getRoomNum();
	text << "), (12,";
	text << GameData::getInGameData()->getLevel();
	text << "), (13,";
	text << GameData::getInGameData()->getMonsterKill();
	text << "), (20,";
	text << (GameData::getInGameData()->getMapDataNumber(0)->HasMonster() ? 0 : 1);
	text << "), (21,";
	text << GameData::getInGameData()->getMapDataNumber(0)->getType();
	text << "), (22,";
	text << (GameData::getInGameData()->getMapDataNumber(0)->getIsItemParm() ? 0 : 1);
	text << "), (23,";
	text << (GameData::getInGameData()->getMapDataNumber(1)->HasMonster() ? 0 : 1);
	text << "), (24,";
	text << GameData::getInGameData()->getMapDataNumber(1)->getType();
	text << "), (25,";
	text << (GameData::getInGameData()->getMapDataNumber(1)->getIsItemParm() ? 0 : 1);
	text << "), (26,";
	text << (GameData::getInGameData()->getMapDataNumber(2)->HasMonster() ? 0 : 1);
	text << "), (27,";
	text << GameData::getInGameData()->getMapDataNumber(2)->getType();
	text << "), (28,";
	text << (GameData::getInGameData()->getMapDataNumber(2)->getIsItemParm() ? 0 : 1);
	text << "), (40,";
	text << GameData::getPlayer()->getHP();
	text << "), (41,";
	text << GameData::getPlayer()->getHunger();
	text << "), (42,";
	text << GameData::getPlayer()->getAttack();
	text << "), (43,";
	text << GameData::getPlayer()->getCommuPower();
	text << "), (44,";
	text << GameData::getPlayer()->getDepence();
	text << "), (45,";
	text << GameData::getPlayer()->getHit();
	text << "), (46,";
	text << GameData::getPlayer()->getEva();
	text << "), (47,";
	text << GameData::getPlayer()->getDevil();
	text << "), (48,";
	text << GameData::getPlayer()->getAngel();
	text << "), (49,";
	if (GameData::getPlayer()->getEquipItem(0) != NULL)
		text << GameData::getPlayer()->getEquipItem(0)->getType();
	else
		text << 0;
	text << "), (50,";
	if (GameData::getPlayer()->getEquipItem(1) != NULL)
		text << GameData::getPlayer()->getEquipItem(1)->getType();
	else
		text << 0;
	text << ")";
	std::string query = text.str();
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("insertDataDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::saveItemList()
{
		deleteItemList();
		if (GameData::getPlayer()->PlayerItemIndex() != 0) {
			std::ostringstream text;
			text.str("");
			text.clear();
			text << "insert into HD_ITEM values (";
			for (int i = 0; i < GameData::getPlayer()->PlayerItemIndex(); i++) {
				if (i > 0)
					text << ", (";
				text << GameData::getPlayer()->getItemBag(i)->getItem()->getType();
				text << ", ";
				text << GameData::getPlayer()->getItemBag(i)->getItemNum();
				text << ")";
			}
			std::string query = text.str();
			_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

			if (_result == SQLITE_OK) {
				log("insertItemDB() SUCCESS");
			}
			else
				log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
		}
}

void DatabaseManager::saveMonster()
{
	deleteMonster();
	std::ostringstream text;
	text.str("");
	text.clear();
	text << "insert into HD_MONSTER values (";
	
	for (int i = 0; i < 3; i++) {
		if (i > 0)
			text << ", (";
		text << i; //roomNum
		if (GameData::getInGameData()->getMapDataNumber(i)->HasMonster()) {
			text << ", ";;
			text << GameData::getInGameData()->getMapDataNumber(i)->getMonster()->getType();
			text << ", ";
			text << GameData::getInGameData()->getMapDataNumber(i)->getMonster()->getHP();
			text << ", ";
			text << GameData::getInGameData()->getMapDataNumber(i)->getMonster()->getWeak();
			text << ", ";
			text << GameData::getInGameData()->getMapDataNumber(i)->getMonster()->getAttack();
			text << ", ";
			text << GameData::getInGameData()->getMapDataNumber(i)->getMonster()->getDepence();
		}
		else {
			text << ", 20, 0, 0, 0, 0";
		}
		text << ")";
	}
	std::string query = text.str();
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("insertMonsterDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::deleteAllData()
{
	deleteDataToDB();
	deleteItemList();
	deleteMonster();
}

void DatabaseManager::deleteDataToDB()
{
	std::string query = "delete from HD_DATA";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("deleteDataDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::deleteItemList()
{
	std::string query = "delete from HD_ITEM";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("deleteItemDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

void DatabaseManager::deleteMonster()
{
	std::string query = "delete from HD_MONSTER";
	sqlite3_stmt *stmt = NULL;
	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("deleteMonsterDB() SUCCESS");
	}
	else
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}
