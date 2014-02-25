#pragma once

#ifndef __SCISSOR__SPRITE__NODE__
#define __SCISSOR__SPRITE__NODE__
#include "cocos2d.h"

class ScissorSpriteNode:public cocos2d::Sprite
{
public:
	~ScissorSpriteNode();

	void visit();
private:
	ScissorSpriteNode();

};

#endif