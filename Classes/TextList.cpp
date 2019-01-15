#include "TextList.h"
#pragma execution_character_set("UTF-8")

USING_NS_CC;


TextList::TextList()
{
	head = NULL;
}


TextList::~TextList()
{
}

std::string TextList::getText(int num)
{
	return getTextNode(num)->getText();
}

TextNode * TextList::getTextNode(int num)
{
	TextNode* temp = head;
	while (temp->getNum() < num && temp->getLink() != NULL)
		temp = temp->getLink();
	return temp;
}

void TextList::add(TextNode * node)
{
	if (head == NULL) {
		head = node;
		node->setLink(NULL);
	}
	else {
		TextNode* temp = head;
		while (temp->getLink() != NULL)
			temp = temp->getLink();
		temp->setLink(node);
		node->setLink(NULL);
	}
}

std::string TextList::pop()
{
	std::string result = head->getText();
	TextNode* temp = head->getLink();
	delete(head);
	head = temp;
	return result;
}

int TextList::lastNodeNum()
{
	int num = 0;
	TextNode* temp = head;
	while (temp->getLink() != NULL)
		temp = temp->getLink();
	return temp->getNum();
}
