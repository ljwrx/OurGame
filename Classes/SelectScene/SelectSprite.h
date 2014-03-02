#pragma once

#ifndef __SELECT__SPRITE__
#define __SELECT__SPRITE__
#include "ScissorSpriteNode.h"

class SelectSprite : public ScissorSpriteNode
{
public:
	~SelectSprite();

	int CheckPointIn(cocos2d::Point& touch_point);

	void MoveUp(int dy){};
	void MoveDown(int dx){};

	virtual bool init(const std::string& filename, int data, bool flag);
	static SelectSprite* create(const std::string& filename, int data, bool flag);

protected:
	SelectSprite();
	void _setImageFromData(int data, bool flag);
};

#endif
