#include "SelectSprite.h"
#include "Tool.h"

#ifndef SELECT__DATA__MAX
#define SELSCT__DATA__MAX 32
#endif
USING_NS_CC;
SelectSprite::SelectSprite()
{
}

SelectSprite::~SelectSprite()
{
}

/////////////////////////////////////////////////////////////////////////
///////           关于构造方法            ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

void SelectSprite::_setImageFromData(int data, bool flag)
{
	char ch;
	int count = 0;
	cocos2d::String str;
	Sprite* temp = nullptr;
	Layer* layer = Layer::create();
	int positionY = this->getContentSize().height / 2;

	if (flag)
		ch = 's';
	else
		ch = 'i';

	for (int index = 0; index < SELSCT__DATA__MAX; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			str.initWithFormat("\\res\\%s\\icon\\%d.png", ch, index);
			temp = Sprite::create(str.getCString());
			temp->setPosition(5 + temp->getContentSize().width*index, positionY);
			layer->addChild(temp);
		}
	}

	layer->setAnchorPoint(Point::ZERO);
	this->setAnchorPoint(Point::ZERO);
	layer->setPosition(Point::ZERO);
	this->addChild(layer);

}

bool SelectSprite::init(const std::string& filename, int data, bool flag)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;
	_setImageFromData(data, flag);
	return true;

}

SelectSprite* SelectSprite::create(const std::string& filename, int data, bool flag)
{
	SelectSprite *sprite = new SelectSprite();
	if (sprite && sprite->init(filename, data, flag))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


//其他方法

int SelectSprite::CheckPointIn(cocos2d::Point& touch_point)
{
	if (!this->boundingBox().containsPoint(touch_point))
		return 0;

}