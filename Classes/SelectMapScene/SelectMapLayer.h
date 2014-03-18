
#ifndef __SELECT__MAP__LAYER__
#define __SELECT__MAP__LAYER__

#include "cocos2d.h"

class SelectMapLayer : public cocos2d::Menu
{
public:
	~SelectMapLayer();

	//
	int resetItemsZOrder();
	cocos2d::MenuItem* checkNearSel();

	//´¥ÃþÏà¹Ø
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	bool initWithArray(int r, const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems);

	static SelectMapLayer* createWithArray(int r, const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems);
	static SelectMapLayer* create(int r, cocos2d::MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
	static SelectMapLayer* createWithItems(int r, cocos2d::MenuItem *firstItem, va_list args);
private: 
	SelectMapLayer();
	void _setItemVisibleInfoPosition(cocos2d::Node* node);
private:
	int _r;//°ë¾¶
	cocos2d::Point _lastTouch;
};

#endif