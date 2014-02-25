#pragma once

#ifndef __SELECT__LAYER__
#define __SELECT__LAYER__

#include "cocos2d.h"

class SelectLayer :public cocos2d::Layer
{
public:
	~SelectLayer();
	bool initWithData(int data, int canSel);
	static SelectLayer* createWithData(int data, int canSel);
private:
	SelectLayer();
};


#endif