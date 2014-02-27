#pragma once

#ifndef __SCISSOR__SPRITE__NODE__
#define __SCISSOR__SPRITE__NODE__
#include "cocos2d.h"

class ScissorSpriteNode:public cocos2d::Sprite
{
public:
	ScissorSpriteNode();
	~ScissorSpriteNode();

	static ScissorSpriteNode* create();
	static ScissorSpriteNode* create(const std::string& filename);
	static ScissorSpriteNode* create(const std::string& filename, const cocos2d::Rect& rect);

	static ScissorSpriteNode* createWithTexture(cocos2d::Texture2D *texture);
	static ScissorSpriteNode* createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated = false);

	static ScissorSpriteNode* createWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);
	static ScissorSpriteNode* createWithSpriteFrameName(const std::string& spriteFrameName);

	void visit();
};

#endif