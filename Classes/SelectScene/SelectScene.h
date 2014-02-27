#pragma once

#ifndef __SELECT__SCENE__
#define __SELECT__SCENE__
#include "cocos2d.h"
class SelectScene :public cocos2d::Scene
{
public:
	~SelectScene();

	bool initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);

	//s_canUse 士兵的是否可用标识
	//s_canSel 士兵可选择上场的最大总数
	//i_canUse 物品是否可用标识
	//i_canSel 物品可选择上场的最大总数
	static SelectScene* createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);
private:
	SelectScene();
private:

};

#endif