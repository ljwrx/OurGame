
#ifndef __SELECT__MAP__SPRITE__
#define __SELECT__MAP__SPRITE__

#include "cocos2d.h"

enum GearKind
{
	BIG_GEAR = 0xFFFFFFFF,
	SML_GEAR = 0xFFFFFF00
};

class GearSprite : public cocos2d::Sprite
{
public:
	~GearSprite();

	//获取当前选中的地图index
	int getSelectingMapIndex(void);
	void resetChildPosition(void);


	//触摸相关

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	//构造器
	bool initWithData(unsigned int data);
	bool initWithData(unsigned int data, unsigned int mapIndex);
	bool initWithKind(GearKind kind, unsigned int data);
	static GearSprite* createWithKind(GearKind kind, unsigned int data);

protected:
	GearSprite();
private:
	void _stopAllActions(void);
private:
	GearKind tag;
	cocos2d::Point _lastTouch;
};

#endif