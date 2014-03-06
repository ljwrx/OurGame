#include "SelectLayer.h"
#include "SelectSprite.h"
#include "..\Tool.h"
USING_NS_CC;

#ifndef SELECT__CHECK__MAX
#define SELECT__CHECK__MAX 32
#endif

#define POINT__NOT__IN__SPRITE 0
#define POINT__IN__SPRITE__INDEX(__index__) ++__index__
#define INDEX__IN__SPRITE__LISTS(__index__) --__index__

#define GET__SELECT__LAYER__INDEX TOOL::GetHigData(_selectIndex)
#define GET__SELECT__SPRITE__INDEX TOOL::GetLowData(_selectIndex)
#define SET__SELECT__LAYER__INDEX(__index__) TOOL::SetHigOrLowData(_selectIndex, __index__, 1)
#define SET__SELECT__SPRITE__INDEX(__index__) TOOL::SetHigOrLowData(_selectIndex, __index__, 0)

#define CANDIDATE_S_LAYER_TAG 0
#define CANDIDATE_I_LAYER_TAG 1
#define SELECTING_S_LAYER_TAG 2
#define SELECTING_I_LAYER_TAG 3

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
	Layer::setTouchEnabled(true);
	Layer::setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	Sprite* sp = SelectSprite::createWithData("\\res\\SelectScene\\select_candidate.png", _sList, s_canUse, 0);
	sp->setPosition(0,0);
	this->addChild(sp, 4, 0);

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

int SelectLayer::_checkListInfoTouchPoint(cocos2d::Point& touch_point, cocos2d::Vector<cocos2d::Sprite*>& list)
{
	int Max = list.size();
	for (int index = 0; index < Max; ++index)
	{
		if (list.at(index)->getBoundingBox().containsPoint(touch_point))
			return POINT__IN__SPRITE__INDEX(index);
	}
	return POINT__NOT__IN__SPRITE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////					´¥ÃþÏà¹Ø						//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SelectLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	int layerIndex = 0;
	int spriteIndex = 0;
	_nowTouchPoint = touch->getLocation();

	if (((SelectSprite*)(this->getChildByTag(CANDIDATE_S_LAYER_TAG)))->CheckPointIn(_nowTouchPoint))
		layerIndex = CANDIDATE_S_LAYER_TAG;
	else if (((SelectSprite*)(this->getChildByTag(CANDIDATE_I_LAYER_TAG)))->CheckPointIn(_nowTouchPoint))
		layerIndex = CANDIDATE_I_LAYER_TAG;
	else if (((SelectSprite*)(this->getChildByTag(SELECTING_S_LAYER_TAG)))->CheckPointIn(_nowTouchPoint))
		layerIndex = SELECTING_S_LAYER_TAG;
	else if (((SelectSprite*)(this->getChildByTag(SELECTING_I_LAYER_TAG)))->CheckPointIn(_nowTouchPoint))
		layerIndex = SELECTING_I_LAYER_TAG;
	else
		return false;
	SET__SELECT__LAYER__INDEX(layerIndex);

	return true;
}

void SelectLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point now = touch->getLocation();
	int selectLayerIndex = GET__SELECT__LAYER__INDEX;
	Point delte(now.x - _nowTouchPoint.x, now.y - _nowTouchPoint.y);
	((SelectSprite*)this->getChildByTag(0))->Move(delte.x, 0);

	SET__SELECT__SPRITE__INDEX(POINT__NOT__IN__SPRITE);
	_nowTouchPoint = now;
}

void SelectLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	int spriteIndex = 0;
	int layerIndex = GET__SELECT__LAYER__INDEX;

	if ((layerIndex == CANDIDATE_S_LAYER_TAG) || (layerIndex == SELECTING_S_LAYER_TAG))
		spriteIndex = _checkListInfoTouchPoint(_nowTouchPoint, _sList);

	else if ((layerIndex == CANDIDATE_I_LAYER_TAG) || (layerIndex == SELECTING_I_LAYER_TAG))
		spriteIndex = _checkListInfoTouchPoint(_nowTouchPoint, _iList);

	if (spriteIndex == 0)
		return;
	else if (spriteIndex == GET__SELECT__SPRITE__INDEX)
	{
		int a = 0;
	}
	else
		SET__SELECT__SPRITE__INDEX(spriteIndex);
}

void SelectLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
}