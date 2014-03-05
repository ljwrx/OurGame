#pragma once

#ifndef __SELECT__SPRITE__
#define __SELECT__SPRITE__
#include "ScissorSpriteNode.h"

class SelectSprite : public ScissorSpriteNode
{
public:
	~SelectSprite();

	bool CheckPointIn(cocos2d::Point& touch_point);

	//delta	�ƶ��ķ���
	//flag	0Ϊx�� 1Ϊy��
	void Move(float delta, bool flag);

	//sprite	Ҫ����ľ���
	//flag		0Ϊ��ѡ 1Ϊ��ѡ
	void InsterSprite(cocos2d::Sprite* sprite, bool flag);

	//index		Ҫȡ���ľ������ڵ�index
	//flag		0Ϊ��ѡ 1Ϊ��ѡ
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
	int _count;//��ǰӵ�е�����
};

#endif
