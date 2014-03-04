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
	Layer::setTouchEnabled(true);
	Layer::setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	Sprite* sp = SelectSprite::createWithData("\\res\\SelectScene\\select_candidate.png", s_canUse, 0);
	sp->setPosition(0,0);
	this->addChild(sp, 4, 0);

	//ScissorSpriteNode* node = ScissorSpriteNode::create("\\res\\SelectScene\\select_candidate.png");
	//node->setAnchorPoint(Point::ZERO);
	//node->setPosition(0, 0);

	//Sprite* sp = Sprite::create("\\res\\SelectScene\\select_s_box.png");
	//sp->setAnchorPoint(Point::ZERO);
	//sp->setPosition(0, 100);
	//node->addChild(sp);


	//this->addChild(node);

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////					´¥ÃþÏà¹Ø						//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SelectLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	int index = 0;
	_nowTouchPoint = touch->getLocation();
	Vector<Node*> child((this->getChildren()));

	if ((index = ((SelectSprite*)child.at(0))->CheckPointIn(_nowTouchPoint)))
	{
		TOOL::SetHigOrLowData(_selectIndex, 0, 1);
		TOOL::SetHigOrLowData(_selectIndex, index, 0);
		return true;
	}

	return false;
}

void SelectLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point now = touch->getLocation();
	int selectLayerIndex = TOOL::GetHigData(_selectIndex);
	Point delte(now.x - _nowTouchPoint.x, now.y - _nowTouchPoint.y);
	((SelectSprite*)this->getChildByTag(0))->Move(delte.x, 0);
	_nowTouchPoint = now;
}

void SelectLayer::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void SelectLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
	return;
}