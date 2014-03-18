
#include "SelectMapLayer.h"

USING_NS_CC;

#define Deviation 10

SelectMapLayer::SelectMapLayer()
{
}

SelectMapLayer::~SelectMapLayer()
{
}

SelectMapLayer* SelectMapLayer::createWithArray(int r, const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems)
{
	auto ret = new SelectMapLayer();
	if (ret && ret->initWithArray(r ,arrayOfItems))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

SelectMapLayer* SelectMapLayer::create(int r, cocos2d::MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	SelectMapLayer *ret = SelectMapLayer::createWithItems(r, item, args);

	va_end(args);

	return ret;
}

SelectMapLayer* SelectMapLayer::createWithItems(int r, cocos2d::MenuItem *firstItem, va_list args)
{
	Vector<MenuItem*> items;
	if (firstItem)
	{
		items.pushBack(firstItem);
		MenuItem *i = va_arg(args, MenuItem*);
		while (i)
		{
			items.pushBack(i);
			i = va_arg(args, MenuItem*);
		}
	}

	return SelectMapLayer::createWithArray(r, items);
}

bool SelectMapLayer::initWithArray(int r, const cocos2d::Vector<MenuItem*>& arrayOfItems)
{
	if (!Menu::initWithArray(arrayOfItems))
		return false;
	_r = r;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////		´¥ÃþÏà¹Ø		//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

bool SelectMapLayer::onTouchBegan(Touch* touch, Event* event)
{

	Point tou = touch->getLocation();
	Point loc = this->convertToNodeSpace(tou);
	
	float dx = loc.x - tou.x;
	float dy = loc.y - tou.y;
	float Rr = this->_r + Deviation;

	if (dx*dx + dy*dy <= Rr*Rr)
	{
		_lastTouch = tou;
		return true;
	}
	return false;
}

void SelectMapLayer::onTouchEnded(Touch* touch, Event* event)
{

}

void SelectMapLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void SelectMapLayer::onTouchMoved(Touch* touch, Event* event)
{
	
}

/////////////////////////////////

void SelectMapLayer::_setItemVisibleInfoPosition(Node* node)
{
	if (node->getPositionX() + node->getContentSize().width / 2 <= 0)
	{
		getChildren().eraseObject(node);
		getChildren().pushBack(node);
		node->setVisible(false);
	}
}

int SelectMapLayer::resetItemsZOrder()
{
	Vector<Node*>list = getChildren();
	int Max = list.size();

	int index = 0;
	int middle = 0;
	
	Sprite* top = (Sprite*)list.at(0);
	Sprite* las = (Sprite*)list.at(Max - 1);

	if (Max % 2)
		middle = (Max + 1) >> 1;
	else
		middle = Max >> 1;


	Sprite* mid = (Sprite*)list.at(middle);
	Sprite* midPlusOne = (Sprite*)list.at(middle + 1);

	_setItemVisibleInfoPosition(top);
	_setItemVisibleInfoPosition(las);
	_setItemVisibleInfoPosition(mid);
	_setItemVisibleInfoPosition(midPlusOne);

	do
	{
		list.at(middle)->setZOrder(index);
		list.at(index)->setZOrder(index);
		++index;
		--middle;
	} while (middle >= index);
	return --index;
}

MenuItem* SelectMapLayer::checkNearSel()
{
	int index = resetItemsZOrder();
	int this_y = getChildByTag(index)->getPositionY();
	int next_y = getChildByTag(index + 1)->getPositionY();

	if (this_y < 0)
		this_y = 0 - this_y;
	if (next_y < 0)
		next_y = 0 - next_y;

	return (this_y < next_y ? (MenuItem*)getChildByTag(index) : (MenuItem*)getChildByTag(index + 1));

}