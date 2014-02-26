#pragma once

#ifndef __SELECT__LAYER__
#define __SELECT__LAYER__

#include "cocos2d.h"

class SelectLayer :public cocos2d::Layer
{
public:
	~SelectLayer();

	//data		�Ƿ���ñ�ʶ����
	//canSel	��ѡ�����������
	//flag		0Ϊʿ��ѡ��Layer��1Ϊ��Ʒ
	bool initWithData(int data, int canSel, bool flag);
	
	//data		�Ƿ���ñ�ʶ����
	//canSel	��ѡ�����������
	//flag		0Ϊʿ��ѡ��Layer��1Ϊ��Ʒ
	static SelectLayer* createWithData(int data, int canSel, bool flag);
	
private:
	SelectLayer();

	void _setImageFromData(int data, bool flag);

private:
	int _count;
	int _selectData;
	cocos2d::Vector<cocos2d::Sprite*> _list;
};


#endif