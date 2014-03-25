#include "SelectMapSprite.h"
#include "Tool.h"

USING_NS_CC;

#define BIG_GEAR_IMAGE_NAME			"res\\SelevtMapRec\\big_gear.png"
#define SML_GEAR_IMAGE_NAME			"res\\SelevtMapRec\\sml_gear.png"

#define BIG_MAP_IMAGE_NAME_FORMAT	"res\\SelevtMapRec\\Map\\%d.png"
#define SML_MAP_IMAGE_NAME_FORMAT	"res\\SelevtMapRec\\Map-%d\\%d.png"

#define Deviation					10
#define PI							3.1415926
#define InRadians360				2*PI
#define InAngle360					360
#define RotateSPD					60

GearSprite::GearSprite()
{

}
GearSprite::~GearSprite()
{

}


////////////////////////////////////////////////////////////////
//////////////////		构造器		////////////////////////////
////////////////////////////////////////////////////////////////

bool GearSprite::initWithData(unsigned int data)
{
	String str;
	int count = 0;
	Sprite* temp = nullptr;
	for (int index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			++count;
			str.initWithFormat(BIG_MAP_IMAGE_NAME_FORMAT, index);
			if (!(temp = Sprite::create(str.getCString())))
				return false;
			this->addChild(temp, count, count);
		}
	}
	resetChildPosition();
	return true;
}

bool GearSprite::initWithData(unsigned int data, unsigned int mapIndex)
{
	String str;
	int count = 0;
	Sprite* temp = nullptr;
	this->removeAllChildren();
	this->setRotation(0);
	for (int index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			++count;
			str.initWithFormat(SML_MAP_IMAGE_NAME_FORMAT, mapIndex, index);
			if (!(temp = Sprite::create(str.getCString())))
				return false;
			this->addChild(temp, count, count);
		}
	}
	resetChildPosition();
	return true;
}

bool GearSprite::initWithKind(GearKind kind, unsigned int data)
{
	tag = kind;
	switch (kind)
	{
	case BIG_GEAR:
		if (!Sprite::initWithFile(BIG_GEAR_IMAGE_NAME))
			return false;
		initWithData(data);
		break;
	case SML_GEAR:
		if (!Sprite::initWithFile(SML_GEAR_IMAGE_NAME))
			return false;
		break;
	default:
		return false;
	}
	return true;
}

GearSprite* GearSprite::createWithKind(GearKind kind, unsigned int data)
{
	GearSprite* p = new GearSprite();
	if (p && p->initWithKind(kind,data))
		p->autorelease();

	else
	{
		if (p)
			delete p;
		p = nullptr;
	}
	return p;
}


//////////////////////////////////////////////////////////////////////////////
/////////////////////////	触摸相关		//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool GearSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Point loc = this->convertToNodeSpaceAR(touch->getLocation());
	float Rr = this->getContentSize().width / 2 + Deviation;
	if (loc.x*loc.x + loc.y*loc.y <= Rr*Rr)
	{
		_stopAllActions();
		_lastTouch = touch->getLocation();
		return true;
	}
	return false;
}
void GearSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (this->getChildrenCount())
	{
		float da = InAngle360 / this->getChildrenCount(); //平均角度
		int index = this->getSelectingMapIndex();
		float deltaAngle = 0;
		if (this->getRotation() >= 0)
			deltaAngle = da*index - this->getRotation();
		else
			deltaAngle = -da*index - this->getRotation();
		this->runAction(RotateBy::create(fabsf(deltaAngle) / RotateSPD, deltaAngle));
		for (auto& child : _children)
			child->runAction(RotateBy::create(fabsf(deltaAngle) / RotateSPD, -deltaAngle));
	}
}
void GearSprite::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
void GearSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Point tou = touch->getLocation();
	float ds = TOOL::PointToPoint(_lastTouch, tou) / PI;
	float nowRotation = this->getRotation();
	this->setRotation(0);
	float dx = this->convertToNodeSpaceAR(tou).x;
	this->setRotation(nowRotation);
	float dy = tou.y - _lastTouch.y;
	do
	{
		switch (dx>=0)
		{
		case true:
			if (dy > 0)
			{
				ds = ds;
			}//if tou.y >= 0
			else if (dy < 0)
			{
				ds = -ds;
			}//else if tou.y < 0
			break;

		case false:
			if (dy > 0)
			{
				ds = -ds;
			}//if tou.y >= 0
			else if (dy < 0)
			{
				ds = ds;
			}//else if tou.y < 0
			break;
		default:
			break;
		}
		

		if (this->getRotation() - ds > -360)
			this->setRotation(this->getRotation() - ds);
		else
			this->setRotation((this->getRotation() - ds) + 360);

		for (auto& child : _children)
			child->setRotation(child->getRotation() + ds);
	} while (0);

	_lastTouch = tou;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////	其他函数		//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int GearSprite::getSelectingMapIndex(void)
{
	float nowRotation = this->getRotation();
	return abs(floorf(nowRotation / InAngle360 * this->getChildrenCount() + 0.5));
}

void GearSprite::resetChildPosition(void)
{
	int count = 0;
	Point pos = Point::ZERO;
	float R = this->getContentSize().width / 2;
	float da = InRadians360 / this->getChildrenCount(); //平均角度
	float dx = this->getContentSize().width / 2;
	float dy = this->getContentSize().height / 2;
	int flag = 0;
	switch (tag)
	{
	case BIG_GEAR:
		flag = 0;
		break;
	case SML_GEAR:
		flag = 1;
		break;
	default:
		break;
	}
	for (auto child : _children)
	{
		child->setPositionX(R*cos(flag*PI + da * count) + dx);
		child->setPositionY(R*sin(flag*PI + da * count) + dy);
		++count;
	}
}


void GearSprite::_stopAllActions(void)
{
	this->stopAllActions();
	for (auto child : _children)
		child->stopAllActions();
}