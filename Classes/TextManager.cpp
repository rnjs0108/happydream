#include "TextManager.h"
#include "cocos2d.h"
#include "GameData.h"
#pragma execution_character_set("UTF-8")
USING_NS_CC;
using namespace std;


TextManager::TextManager()
{
	list = new TextList();
}


TextManager::~TextManager()
{
}

void TextManager::createText(std::string path)
{
	resetText();
	std::string Path = "bin/text/" + path;
    std::string filePath = FileUtils::getInstance()->fullPathForFilename(Path);
    std::string textData = FileUtils::getInstance()->getStringFromFile(filePath);
	splitAndNodePush(textData, "\n");
}
void TextManager::resetText()
{
	delete list;
	list = new TextList();
}

void TextManager::splitAndNodePush(std::string target, std::string delimiter)
{
	vector<std::string> result;
	int position = target.find(delimiter);

	while (position != -1) {
		std::string str1 = target.substr(0, position);
		result.push_back(str1);
		target = target.substr(position + 1);
		position = target.find(delimiter);
	}
	result.push_back(target);

	for (int i = 0; i < result.size(); i++) {
		std::string strbuf = result.at(i);
		if (i == 0) {
			char head[3];
			strbuf = strbuf.substr(sizeof(head), strbuf.length());
		}
		TextNode* newNode = new TextNode(i);
		strbuf = replaceAll(strbuf, "/n", "\n");
		strbuf = findImg(newNode, strbuf);
		newNode->setText(strbuf);
		list->add(newNode);
	}
}

std::string TextManager::replaceAll(std::string str, const char * before, const char * after)
{
	int ipos = str.find(before);
	int beforeLength = strlen(before);

	while (ipos != string::npos) {

		str.replace(ipos, beforeLength, after);
		ipos = str.find(before, ipos);

	}

	return str;
}

std::string TextManager::findImg(TextNode* node, std::string str)
{
	//플레이어 이미지 찾기
	int ipos = str.find("/p");
	int beforeLength = strlen("/p");

	while (ipos != string::npos) {
		//노드의 이미지에 플레이어 이미지를 삽입시켜줌
		node->setImg(0);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/p", ipos);
	}
	//하트의 이미지 찾기
	ipos = str.find("/h");
	beforeLength = strlen("/h");

	while (ipos != string::npos) {
		//노드의 이미지에 하트의 이미지를 삽입시켜줌
		node->setImg(1);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/h", ipos);
	}
	//몬스터의 이미지 찾기
	ipos = str.find("/m");
	beforeLength = strlen("/m");

	while (ipos != string::npos) {
		//노드의 이미지에 몬스터의 이미지를 삽입시켜줌
		node->setImg(2);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/m", ipos);
	}
	//천사의 이미지 찾기
	ipos = str.find("/a");
	beforeLength = strlen("/a");

	while (ipos != string::npos) {
		//노드의 이미지에 천사의 이미지를 삽입시켜줌
		node->setImg(3);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/a", ipos);
	}
	//악마의 이미지 찾기
	ipos = str.find("/d");
	beforeLength = strlen("/d");

	while (ipos != string::npos) {
		//노드의 이미지에 악마의 이미지를 삽입시켜줌
		node->setImg(4);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/d", ipos);
	}
	//상자의 이미지 찾기
	ipos = str.find("/b");
	beforeLength = strlen("/b");

	while (ipos != string::npos) {
		//노드의 이미지에 상자의 이미지를 삽입시켜줌
		node->setImg(5);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/b", ipos);
	}
	//흔들림이펙트
	ipos = str.find("/!");
	beforeLength = strlen("/!");

	while (ipos != string::npos) {
		//노드의 이미지에 몬스터의 이미지를 삽입시켜줌
		node->setEffect(1);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/!", ipos);
	}

	//???이름
	ipos = str.find("/?");
	beforeLength = strlen("/?");

	while (ipos != string::npos) {
		//노드의 이미지에 몬스터의 이미지를 삽입시켜줌
		node->setName("???");
		node->setEffect(9);
		str.replace(ipos, beforeLength, "");
		ipos = str.find("/?", ipos);
	}

	return str;
}

void TextManager::test()
{
	while (list->canPop()) {
		log("%s", list->pop().c_str());
	}
}

std::string TextManager::getText()
{
	std::string result = getTextList()->getText(GameData::getInGameData()->getCommuNum());
	return result;
}

TextNode * TextManager::getTextNode()
{
	TextNode* result = getTextList()->getTextNode(GameData::getInGameData()->getCommuNum());
	return result;
}

int TextManager::getTextNum()
{
	int result = getTextList()->getTextNode(GameData::getInGameData()->getCommuNum())->getNum();
	return result;
}
