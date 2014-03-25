
#ifndef __SELECT__MAP__LAYER__
#define __SELECT__MAP__LAYER__

#include "cocos2d.h"

class SelectMapLayer : public cocos2d::Layer
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

	void onEnter(void);

	bool initWithData(int _r, unsigned int data);
	static SelectMapLayer* createWithData(int r, unsigned int data);

private: 
	SelectMapLayer();
	void _setItemVisibleInfoPosition(cocos2d::Node* node);
	void _showSmlGear(void);
	void _hideSmlGear(void);
	void _setSmlGearVisible(cocos2d::Node*, void* flag);
	int _loadMapDataFromFile(int mapIndex);

	void _hideMapCover();
	void _showMapCover();
	void _hideLevelCover();
	void _showLevelCover();

private:
	int _selectingGear;
	cocos2d::Point _lastTouch;
	std::string _levelData;
};

#endif