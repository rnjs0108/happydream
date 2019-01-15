#pragma once
#include "TextList.h"
#include <vector>
class TextManager
{
private:
	TextList * list;
public:
	TextManager();
	~TextManager();
	void createText(std::string path); //대화생성 알고리즘
	void resetText(); //대화 초기화

	void splitAndNodePush(std::string target, std::string delimiter);
	std::string replaceAll(std::string str, const char* before, const char* after);
	std::string findImg(TextNode* node, std::string str);
	void test(); //노드 저장 테스트

	std::string getText();
	TextNode* getTextNode();
	int getTextNum();
	TextList* getTextList() { return list; }
};

