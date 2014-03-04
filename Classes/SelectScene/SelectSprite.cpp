#include "SelectSprite.h"
#include "Tool.h"

#ifndef SELECT__DATA__MAX
#define SELSCT__DATA__MAX 32
#endif

#ifndef CHECK__NOT__IN__SPRITE
#define CHECK__NOT__IN__SPRITE 0x0000FFFF
#endif

#ifndef LAYER__IN__SPRITE__TAG
#define LAYER__IN__SPRITE__TAG 0
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
		ch = 'i';
	else
		ch = 's';

	for (int index = 0; index < SELSCT__DATA__MAX; ++index)
	{
		if (TOOL::GetBinNum(data, index+1))
		{
			str.initWithFormat("\\res\\%c\\icon\\%d.png", ch, index);
			temp = Sprite::create(str.getCString());
			temp->setPosition(temp->getContentSize().width*(0.5+(count++)), positionY);
			layer->addChild(temp, index, index);
		}
	}

	layer->setAnchorPoint(Point::ZERO);
	this->setAnchorPoint(Point::ZERO);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 0, LAYER__IN__SPRITE__TAG);

}

bool SelectSprite::initWithData(const std::string& filename, int data, bool flag)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;
	_setImageFromData(data, flag);
	return true;

}

SelectSprite* SelectSprite::createWithData(const std::string& filename, int data, bool flag)
{
	SelectSprite *sprite = new SelectSprite();
	if (sprite && sprite->initWithData(filename, data, flag))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool SelectSprite::initWithCountMax(const std::string& filename, int max, bool flag)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;
	char* ch;
	Sprite* temp = nullptr;
	Layer* layer = Layer::create();
	int positionX = this->getContentSize().width / 2;

	if (flag)
		ch = "\\res\\SelectScene\\select_i_box.png";
	else
		ch = "\\res\\SelectScene\\select_s_box.png";

	for (int index = 0; index < max; ++index)
	{
		temp = Sprite::create(ch);
		temp->setPosition(positionX, temp->getContentSize().height*(0.5 + index));
		layer->addChild(temp, index, index);
	}

	layer->setAnchorPoint(Point::ZERO);
	this->setAnchorPoint(Point::ZERO);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 0, LAYER__IN__SPRITE__TAG);
	return true;
}

SelectSprite* SelectSprite::createWithCountMax(const std::string& filename, int max, bool flag)
{
	SelectSprite *sprite = new SelectSprite();
	if (sprite && sprite->initWithCountMax(filename, max, flag))
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
	if (!this->getBoundingBox().containsPoint(touch_point))
		return 0;
	Layer* layer = (Layer*)(this->getChildByTag(LAYER__IN__SPRITE__TAG));
	int checkMax = layer->getChildrenCount();

	for (int index = 0; index < checkMax; ++index)
	{
		if (layer->getChildByTag(index)->getBoundingBox().containsPoint(touch_point))
			return index + 1;
	}
	return CHECK__NOT__IN__SPRITE;
}

void SelectSprite::Move(float delta, bool flag)
{
	Layer*	layer	= (Layer*)(this->getChildByTag(LAYER__IN__SPRITE__TAG));
	Point	pos		= layer->getPosition();

	if (flag)
		layer->setPositionY(pos.y + delta);
	else
		layer->setPositionX(pos.x + delta);
}