#pragma once

#ifndef __SELECT__SCENE__
#define __SELECT__SCENE__
#include "cocos2d.h"
class SelectScene :public cocos2d::Scene
{
public:
	~SelectScene();

	bool initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);

	//s_canUse ʿ�����Ƿ���ñ�ʶ
	//s_canSel ʿ����ѡ���ϳ����������
	//i_canUse ��Ʒ�Ƿ���ñ�ʶ
	//i_canSel ��Ʒ��ѡ���ϳ����������
	static SelectScene* createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel);
private:
	SelectScene();
private:

};

#endif