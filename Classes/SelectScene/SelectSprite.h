#pragma once

#ifndef __SELECT__SPRITE__
#define __SELECT__SPRITE__
#include "ScissorSpriteNode.h"

class SelectSprite : public ScissorSpriteNode
{
public:
	~SelectSprite();

	int CheckPointIn(cocos2d::Point& touch_point);

	//delta	�ƶ��ķ���
	//flag	0Ϊx�� 1Ϊy��
	void Move(float delta, bool flag);

	virtual bool initWithData(const std::string& filename, int data, bool flag);
	static SelectSprite* createWithData(const std::string& filename, int data, bool flag);

	virtual bool initWithCountMax(const std::string& filename, int max, bool flag);
	static SelectSprite* createWithCountMax(const std::string& filename, int max, bool flag);

protected:
	SelectSprite();
	void _setImageFromData(int data, bool flag);
};

#endif
