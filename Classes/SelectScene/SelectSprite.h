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

	bool CheckIsCanRemove();

	//sprite	要插入的精灵
	//flag		0为待选 1为已选
	void InsterSprite(cocos2d::Sprite* sprite, bool flag);

	//flag		0为待选 1为已选
	//从Layer中移除Child;
	void removeChildFromLayer(cocos2d::Node* child, bool flag, bool cleanup = true);

	//flag		0为待选 1为已选
	//重新设置Layer中Child的坐标
	inline void resetChildInLayerInfoCount(bool flag);

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
	int _countMax;//上限
	cocos2d::Vector<cocos2d::Sprite*> _list;
};

#endif
