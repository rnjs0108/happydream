#include "TextNode.h"
#pragma execution_character_set("UTF-8")


TextNode::TextNode(int n)
{
	num = n;
	effect = 0;
	text = "";
	link = NULL;
	img = 0;
	//img = NULL;
}


TextNode::~TextNode()
{
}

void TextNode::setImg(int num) //0:주인공, 1:하트, 2:몬스터, 3:천사, 4:악마
{
	switch (num) {
	case 0:
		log("playerInit");
		name = "주인공";
		//img = CCSprite::create("gfx/player/player.png");
		break;
	case 1:
		log("heartInit");
		name = "하트";
		//img = CCSprite::create("gfx/player/heart.png");
		break;
	case 2:
		name = "몬스터";
		//img = CCSprite::create("gfx/player/monster.png");
		break;
	case 3:
		name = "천사 조각상";
		//img = CCSprite::create("gfx/player/angel.png");
		break;
	case 4:
		name = "악마 조각상";
		//img = CCSprite::create("gfx/player/devil.png");
		break;
	case 5:
		name = "황금 상자";
		break;
	default:
		break;
	}
	img = num;
}
