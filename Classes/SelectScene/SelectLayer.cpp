#include "SelectLayer.h"
#include "SelectSprite.h"
#include "..\Tool.h"
USING_NS_CC;

#ifndef SELECT__CHECK__MAX
#define SELECT__CHECK__MAX 32
#endif

SelectLayer::SelectLayer()
{

}

SelectLayer::~SelectLayer()
{

}


bool SelectLayer::initWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel)
{
	if (!Layer::init())
		return false;

	//¸ÃÍ¼²ã¼ÓÈë´¥ÃþÅÐ¶Ï
//	this->setTouchEnabled(true);
//	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	Sprite* sp = SelectSprite::create("\\res\\SelectScene\\select_candidate.png", s_canUse, 0);
	sp->setPosition(0,0);
	this->addChild(sp);
	return true;
}

SelectLayer* SelectLayer::createWithData(int s_canUse, int s_canSel, int i_canUse, int i_canSel)
{
	SelectLayer* pRet = new SelectLayer();
	if (pRet && pRet->initWithData(s_canUse, s_canSel, i_canUse, i_canSel))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}