#pragma once
#include "sqlite3.h"
#include "cocos2d.h"

using namespace cocos2d;

class DatabaseManager
{
private:
	
	sqlite3 *_sqlite;

public:
	DatabaseManager();
	~DatabaseManager();

	//에러메시지를 담을 변수
	char *_errorMSG;

	//결과의 상태를 담을 변수
	int _result;

	static DatabaseManager *getInstance();
	void createDB();
	bool openDB();
	void closeDB();

	void loadAllData();
	void loadSettingData();
	void loadDataToDB();
	void loadItemList();
	void loadMonster();

	void saveAllData();
	void saveSettingData();
	void updateSettingData();
	void saveDataToDB();
	void saveItemList();
	void saveMonster();

	void deleteAllData();
	void deleteDataToDB();
	void deleteItemList();
	void deleteMonster();
};
