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

	//获取窗口大小
	Size winSize = cocos2d::Director::getInstance()->getWinSize();

	//该图层加入触摸判断
	Layer::setTouchEnabled(true);
	Layer::setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	

	Sprite* s_candidate = SelectSprite::createWithData("\\res\\SelectScene\\select_candidate.png", _sList, s_canUse, false);
	Sprite* i_candidate = SelectSprite::createWithData("\\res\\SelectScene\\select_candidate.png", _iList, i_canUse, true);
	Sprite* s_selecting = SelectSprite::createWithCountMax("\\res\\SelectScene\\select_selecting.png", s_canSel, false);
	Sprite* i_selecting = SelectSprite::createWithCountMax("\\res\\SelectScene\\select_selecting.png", i_canSel, true);

	//设置UI
	s_candidate->setAnchorPoint(Point::ZERO);
	i_candidate->setAnchorPoint(Point::ZERO);
	s_selecting->setAnchorPoint(Point::ZERO);
	i_selecting->setAnchorPoint(Point::ZERO);

	int yForUi = winSize.height/2;

	s_candidate->setPosition(0, 0);
	i_candidate->setPosition(0, winSize.height-i_candidate->getContentSize().height);
	s_selecting->setPosition(winSize.width*0.2, yForUi - s_selecting->getContentSize().height/2);
	i_selecting->setPosition(winSize.width*0.8 - i_selecting->getContentSize().width, yForUi - i_selecting->getContentSize().height / 2);

	this->addChild(s_candidate, 4, CANDIDATE_S_LAYER_TAG);
	this->addChild(i_candidate, 3, CANDIDATE_I_LAYER_TAG);
	this->addChild(s_selecting, 2, SELECTING_S_LAYER_TAG);
	this->addChild(i_selecting, 1, SELECTING_I_LAYER_TAG);

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

Rect SelectLayer::_getSelectSpriteBoungBox(cocos2d::Sprite* sp)
{
	Size size = sp->getContentSize();
	int x = sp->getPositionX() + sp->getParent()->getPositionX() + sp->getParent()->getParent()->getPositionX() - sp->getAnchorPoint().x*size.width;
	int y = sp->getPositionY() + sp->getParent()->getPositionY() + sp->getParent()->getParent()->getPositionY() - sp->getAnchorPoint().y*size.height;
	return Rect(x, y, size.width, size.height);
}

int SelectLayer::_checkListInfoTouchPoint(cocos2d::Point& touch_point, cocos2d::Vector<cocos2d::Sprite*>& list)
{
	Rect rect = Rect::ZERO;
	int Max = list.size();

	for (int index = 0; index < Max; ++index)
	{
		rect = _getSelectSpriteBoungBox(list.at(index));
		if (rect.containsPoint(touch_point))
			return POINT__IN__SPRITE__INDEX(index);
	}
	return POINT__NOT__IN__SPRITE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////					触摸相关						//////////////////////////////////
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

	if (layerIndex != GET__SELECT__LAYER__INDEX)//第二次点击时如果不是同一个选择栏则清空当前选中的ICON
	{
		SET__SELECT__LAYER__INDEX(layerIndex);
		SET__SELECT__SPRITE__INDEX(0);
	}

	return true;
}

void SelectLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point now = touch->getLocation();
	int selectLayerIndex = GET__SELECT__LAYER__INDEX;
	Point delte(now.x - _nowTouchPoint.x, now.y - _nowTouchPoint.y);

	switch (selectLayerIndex)
	{
	case CANDIDATE_S_LAYER_TAG:
	case CANDIDATE_I_LAYER_TAG:
		((SelectSprite*)this->getChildByTag(selectLayerIndex))->Move(delte.x, false);
		break;
	case SELECTING_S_LAYER_TAG:
	case SELECTING_I_LAYER_TAG:
		((SelectSprite*)this->getChildByTag(selectLayerIndex))->Move(delte.y, true);
		break;
	default:
		break;
	}

	

	SET__SELECT__SPRITE__INDEX(POINT__NOT__IN__SPRITE);
	_nowTouchPoint = now;
}

void SelectLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	int spriteIndex = 0;
	Sprite* temp = nullptr;
	int layerIndex = GET__SELECT__LAYER__INDEX;

	if ((layerIndex == CANDIDATE_S_LAYER_TAG) || (layerIndex == SELECTING_S_LAYER_TAG))
		spriteIndex = _checkListInfoTouchPoint(_nowTouchPoint, _sList);

	else if ((layerIndex == CANDIDATE_I_LAYER_TAG) || (layerIndex == SELECTING_I_LAYER_TAG))
		spriteIndex = _checkListInfoTouchPoint(_nowTouchPoint, _iList);

	if (spriteIndex == 0)//没有选中ICON
		return;
	else if (spriteIndex == GET__SELECT__SPRITE__INDEX)//第二次点击相同的ICON
	{
		//进行ICON交换
		int index = 2;
		Sprite* temp = nullptr;
		switch (layerIndex)
		{
		case CANDIDATE_S_LAYER_TAG:
			index = 0;
		case SELECTING_S_LAYER_TAG:
			temp = _sList.at(INDEX__IN__SPRITE__LISTS(spriteIndex));
			if (((SelectSprite*)this->getChildByTag(SELECTING_S_LAYER_TAG - index))->CheckIsCanRemove())
			{
				((SelectSprite*)this->getChildByTag(layerIndex))->removeChildFromLayer(temp, index, true);
				((SelectSprite*)this->getChildByTag(SELECTING_S_LAYER_TAG - index))->InsterSprite(temp, !index);
				TOOL::SetBinNum(_s_selectData, spriteIndex, index ? 1 : 0);
			}
			break;

		case CANDIDATE_I_LAYER_TAG:
			index = 0;
		case SELECTING_I_LAYER_TAG:
			temp = _iList.at(INDEX__IN__SPRITE__LISTS(spriteIndex));
			if (((SelectSprite*)this->getChildByTag(SELECTING_S_LAYER_TAG - index))->CheckIsCanRemove())
			{
				((SelectSprite*)this->getChildByTag(layerIndex))->removeChildFromLayer(temp, index, true);
				((SelectSprite*)this->getChildByTag(SELECTING_S_LAYER_TAG - index))->InsterSprite(temp, !index);
				TOOL::SetBinNum(_i_selectData, spriteIndex, index ? 1 : 0);
			}
			break;

		default:
			break;
		}//switch layerIndex
		SET__SELECT__SPRITE__INDEX(0);
	}//else if

	else//点击了其他的ICON
		SET__SELECT__SPRITE__INDEX(spriteIndex);
}

void SelectLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
}