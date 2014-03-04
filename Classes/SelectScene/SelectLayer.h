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
	bool initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);
	
	//data		是否可用标识数据
	//canSel	能选择的种类上限
	//flag		0为士兵选择Layer，1为物品
	static SelectLayer* createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	SelectLayer();
private:
	int _count;
	int _selectData;
	int _selectIndex;
	cocos2d::Point _nowTouchPoint;
};


#endif