#include "SelectScene.h"
#include "Tool.h"
USING_NS_CC;

#ifndef SELECT__CHECK__MAX
#define SELECT__CHECK__MAX 32
#endif
SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

bool SelectScene::initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel)
{
	if (!Scene::init())
		return false;
	
	return true;
}

SelectScene* SelectScene::createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel)
{
	SelectScene* pRet = new SelectScene();
	if (pRet || pRet->initWithData(s_canUse, s_canSel, i_canUse, i_canSel))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}