#pragma once

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class TextNode
{
private:
	std::string text;
	std::string name;
	int num;
	int effect;
	int img; //캐릭터이미지
	TextNode* link;
public:
	TextNode(int ch);
	~TextNode();
	void setNum(int n) { num = n; }
	int getNum() { return num; }
	void setEffect(int n) { effect = n; }
	int getEffect() { return effect; }
	void setImg(int num);
	//CCSprite* getImg() { if (img != NULL) return img; else return NULL; }
	int getImg() { return img; }
	void setText(std::string str) { text = str; }
	std::string getText() { return text; }
	void setName(std::string n) { name = n; }
	std::string getName() { return name; }
	void setLink(TextNode* link) { this->link = link; }
	TextNode* getLink() { return link; }
};

