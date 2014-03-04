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
	bool initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);
	
	//data		�Ƿ���ñ�ʶ����
	//canSel	��ѡ�����������
	//flag		0Ϊʿ��ѡ��Layer��1Ϊ��Ʒ
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