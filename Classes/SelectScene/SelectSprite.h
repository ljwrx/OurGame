#pragma once

#ifndef __SELECT__SPRITE__
#define __SELECT__SPRITE__
#include "ScissorSpriteNode.h"

class SelectSprite : public ScissorSpriteNode
{
public:
	~SelectSprite();

	virtual bool init(const std::string& filename, int data);
	static SelectSprite* create(const std::string& filename, int data);

private:
	SelectSprite();
	void _setImageFromData(int data, bool flag);
};

#endif
