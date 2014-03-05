#pragma once

#ifndef __SELECT__SPRITE__
#define __SELECT__SPRITE__
#include "ScissorSpriteNode.h"

class SelectSprite : public ScissorSpriteNode
{
public:
	~SelectSprite();

	bool CheckPointIn(cocos2d::Point& touch_point);

	//delta	移动的幅度
	//flag	0为x轴 1为y轴
	void Move(float delta, bool flag);

	//sprite	要插入的精灵
	//flag		0为待选 1为已选
	void InsterSprite(cocos2d::Sprite* sprite, bool flag);

	//index		要取出的精灵所在的index
	//flag		0为待选 1为已选
	cocos2d::Sprite* GetSpriteInfoIndex(unsigned int index, bool flag);

	virtual bool initWithData(const std::string& filename, cocos2d::Vector<Sprite*> &list, int data, bool flag);
	static SelectSprite* createWithData(const std::string& filename, cocos2d::Vector<Sprite*> &list, int data, bool flag);

	virtual bool initWithCountMax(const std::string& filename, int max, bool flag);
	static SelectSprite* createWithCountMax(const std::string& filename, int max, bool flag);

protected:
	SelectSprite();
	void _setImageFromData(cocos2d::Vector<Sprite*> &list, int data, bool flag);
	void _setImageFromCountMax(int max, bool flag);

private:
	int _count;//当前拥有的总数
};

#endif
