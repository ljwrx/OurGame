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

#ifndef MAX__Z__ORDER
#define MAX__Z__ORDER 20
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


/////////////////////////////////////From Data

void SelectSprite::_setImageFromData(Vector<Sprite*> &list, int data, bool flag)
{
	char ch;
	_count = 0;
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
			temp->setPosition(temp->getContentSize().width*(0.5+(_count)), positionY);
			layer->addChild(temp, _count, _count);
			_list.pushBack(temp);
			list.pushBack(temp);
			++_count;
		}
	}
	_countMax = _count;
	layer->setAnchorPoint(Point::ZERO);
	this->setAnchorPoint(Point::ZERO);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 0, LAYER__IN__SPRITE__TAG);

}

bool SelectSprite::initWithData(const std::string& filename, Vector<Sprite*> &list, int data, bool flag)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;
	_setImageFromData(list, data, flag);
	return true;

}

SelectSprite* SelectSprite::createWithData(const std::string& filename, Vector<Sprite*> &list, int data, bool flag)
{
	SelectSprite *sprite = new SelectSprite();
	if (sprite && sprite->initWithData(filename, list, data, flag))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


//////////////////////////////////////////////From Max
void SelectSprite::_setImageFromCountMax(int max, bool flag)
{
	char* ch;
	_count = 0;
	_countMax = max;
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
}

bool SelectSprite::initWithCountMax(const std::string& filename, int max, bool flag)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;
	_setImageFromCountMax(max, flag);
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

bool SelectSprite::CheckPointIn(cocos2d::Point& touch_point)
{
	if (!this->getBoundingBox().containsPoint(touch_point))
		return false;
	return true;
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

bool SelectSprite::CheckIsCanRemove()
{
	return _count < _countMax;
}

void SelectSprite::InsterSprite(cocos2d::Sprite* sprite, bool flag)
{
	Size size = this->getContentSize();
	Layer* layer = (Layer*)getChildByTag(LAYER__IN__SPRITE__TAG);
	if (flag)//如果该Sprite是Selecting的
	{
		Point pos = layer->getChildByTag(_count)->getPosition();
		sprite->setPosition(pos);
	}

	else//如果该Sprite是Candidate的
		sprite->setPosition(sprite->getContentSize().width*(0.5 + (_count)), size.height / 2);
	++_count;
	layer->addChild(sprite, MAX__Z__ORDER, _count);
	_list.pushBack(sprite);
	
}

void SelectSprite::removeChildFromLayer(cocos2d::Node* child, bool flag, bool cleanup /*= true*/)
{
	--_count;
	((Layer*)getChildByTag(LAYER__IN__SPRITE__TAG))->removeChild(child, cleanup);
	_list.eraseObject((Sprite*)child, false);
	resetChildInLayerInfoCount(flag);
}

void SelectSprite::resetChildInLayerInfoCount(bool flag)
{
	if (_count == 0)
		return;

	Sprite* temp = nullptr;
	Layer* layer = (Layer*)getChildByTag(LAYER__IN__SPRITE__TAG);
	for (int index = 0; index < _count; ++index)
	{
		temp = (Sprite*)_list.at(index);
		if (flag)
		{
			Point pos = layer->getChildByTag(index)->getPosition();
			temp->setPosition(pos);
		}
		else
			temp->setPosition(temp->getContentSize().width*(0.5 + index), temp->getPositionY());
	}
	
}