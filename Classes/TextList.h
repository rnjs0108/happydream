#pragma once
#include "TextNode.h"
class TextList //head가 번호 0, head뒤로 번호순으로 링크가 붙음
	//또는 pop()형식으로 사용 시 Queue 속성을 띈 채로 사용가능
{
private:
	TextNode * head;
public:
	TextList();
	~TextList();
	bool canPop() { if (head == NULL) return false; else return true; }
	std::string getText(int num);
	TextNode* getTextNode(int num);
	void add(TextNode* node);
	std::string pop();
	int lastNodeNum();
};

