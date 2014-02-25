#include "SelectLayer.h"
#include "Tool.h"
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

void SelectLayer::_setImageFromData(int data, bool flag)
{
	int local;
	int count;
	String str;
	Sprite* temp = nullptr;
	Size winSize = Director::getInstance()->getVisibleSize();
	if (flag)
		local = -1;
	else
		local = 1;

	for (int index = 0; index < SELECT__CHECK__MAX; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			++count;
			if (flag)
				str.initWithFormat("i_%d.png", index);
			else
				str.initWithFormat("s_%d.png", index);
			temp = Sprite::create(str.getCString());
			temp->setAnchorPoint(Point(0.5, 0.5));
		}
	}
}

bool SelectLayer::initWithData(int data, int canSel, bool flag)
{
	if (!Layer::init())
		return false;
	

	return true;
}

SelectLayer* SelectLayer::createWithData(int data, int canSel, bool flag)
{
	SelectLayer* pRet = new SelectLayer();
	if (pRet || pRet->initWithData(data, canSel, flag))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}