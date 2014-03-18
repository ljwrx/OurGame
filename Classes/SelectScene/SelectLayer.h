#pragma once

#ifndef __SELECT__LAYER__
#define __SELECT__LAYER__

#include "cocos2d.h"

class SelectLayer :public cocos2d::Layer
{
public:
	~SelectLayer();

	//data		是否可用标识数据
	//canSel	能选择的种类上限
	//flag		0为士兵选择Layer，1为物品
	bool initWithData(int data, int canSel, bool flag);
	
	//data		是否可用标识数据
	//canSel	能选择的种类上限
	//flag		0为士兵选择Layer，1为物品
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