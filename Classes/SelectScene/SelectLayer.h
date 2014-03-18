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
	static SelectLayer* createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);


	

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	SelectLayer();

	//获取某个SelectSprite内的精灵的包围盒
	cocos2d::Rect _getSelectSpriteBoungBox(cocos2d::Sprite* sp);

	//返回被触摸的对象，0为没有触摸
	//返回的值减去1则为在list中的位置
	int _checkListInfoTouchPoint(cocos2d::Point& touch_point, cocos2d::Vector<cocos2d::Sprite*>& list);
private:
	int _count;
	
	int _selectIndex;
	int _i_selectData;
	int _s_selectData;
	cocos2d::Point _nowTouchPoint;
	cocos2d::Vector<cocos2d::Sprite*> _sList;
	cocos2d::Vector<cocos2d::Sprite*> _iList;
};


#endif