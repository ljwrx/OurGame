
#ifndef __SELECT__MAP__LAYER__
#define __SELECT__MAP__LAYER__

#include "cocos2d.h"

class SelectMapLayer : public cocos2d::Layer
{
public:
	~SelectMapLayer();


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
	void _showSmlGear(void);
	void _hideSmlGear(void);
	void _setSmlGearVisible(cocos2d::Node*, void* flag);
	int _loadMapDataFromFile(int mapIndex);

	void _hideMapCover();
	void _showMapCover();
	void _hideLevelCover();
	void _showLevelCover();

	inline void _lockHide(void){ _isHide = true; };
	inline void _unLockHide(void){ _isHide = false; };

private:
	bool _isHide;
	int _selectingGear;
	cocos2d::Point _lastTouch;
	std::string _levelData;
};

#endif