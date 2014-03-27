
#include "SelectMapLayer.h"
#include "SelectMapSprite.h"
#include "Tool.h"

USING_NS_CC;

#define BIG_GEAR_FOR_X				0.545
#define BIG_GEAR_FOR_Y				0.42
#define SML_GEAR_FOR_X				0.9
#define SML_GEAR_FOR_Y				0.32

#define SML_GEAR_MOVE_SPD			1.0f

#define BG_IN_LAYER_TAG				0
#define BIG_GEAR_IN_LAYER_TAG		1
#define SML_GEAR_IN_LAYER_TAG		2
#define MAP_COVER_IN_LAYER_TAG		3
#define LEVEL_COVER_IN_LAYER_TAG	4
#define MAP_FILE_NAME_PATH			"save\\leveldata.txt"
#define MAP_COVER_IMAGE_NAME_PATH	"res\\SelevtMapRec\\Map-%d\\cover.png"
#define LEVEL_COVER_IMAGE_NAME_PATH	"res\\SelevtMapRec\\Map-%d\\%d_cover.png"


#define Deviation	10
#define PI			3.1415926


SelectMapLayer::SelectMapLayer()
	:_isHide(true)
{
}

SelectMapLayer::~SelectMapLayer()
{
}

SelectMapLayer* SelectMapLayer::createWithData(int r, unsigned int data)
{
	auto ret = new SelectMapLayer();
	if (ret && ret->initWithData(r ,data))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}


bool SelectMapLayer::initWithData(int _r, unsigned int data)
{
	if (!Layer::init())
		return false;
	String str;
	int r = 0;
	int count = 0;
	Sprite* temp = nullptr; 
	unsigned int _data = TOOL::Unlock(data);
	_levelData = FileUtils::getInstance()->getStringFromFile(MAP_FILE_NAME_PATH);


	Size _winSize = Director::getInstance()->getWinSize();


	Sprite* bg = Sprite::create("res\\SelevtMapRec\\BG.png");
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);
	this->addChild(bg, BG_IN_LAYER_TAG, BG_IN_LAYER_TAG);

	GearSprite* big = GearSprite::createWithKind(GearKind::BIG_GEAR, data);
	big->setPosition(-big->getContentSize().width / 2, _winSize.height*BIG_GEAR_FOR_Y);
	big->setVisible(false);
	this->addChild(big, BIG_GEAR_IN_LAYER_TAG, BIG_GEAR_IN_LAYER_TAG);

	GearSprite* sml = GearSprite::createWithKind(GearKind::SML_GEAR, data);
	sml->setPosition(_winSize.width + sml->getContentSize().width / 2, _winSize.height*SML_GEAR_FOR_Y);
	sml->setVisible(false);
	this->addChild(sml, SML_GEAR_IN_LAYER_TAG, SML_GEAR_IN_LAYER_TAG);
	



	//开启touch
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////		触摸相关		//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

bool SelectMapLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (((GearSprite*)this->getChildByTag(BIG_GEAR_IN_LAYER_TAG))->onTouchBegan(touch, event))
	{
		_selectingGear = BIG_GEAR_IN_LAYER_TAG;
		return true;
	}
	else if (((GearSprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG))->onTouchBegan(touch, event))
	{
		_selectingGear = SML_GEAR_IN_LAYER_TAG;
		return true;
	}
	return false;
}

void SelectMapLayer::onTouchEnded(Touch* touch, Event* event)
{
	
	((GearSprite*)this->getChildByTag(_selectingGear))->onTouchEnded(touch, event);
	if (_selectingGear == BIG_GEAR_IN_LAYER_TAG)
	{
		GearSprite* temp = (GearSprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG);
		temp->initWithData(_loadMapDataFromFile(((GearSprite*)this->getChildByTag(_selectingGear))->getSelectingMapIndex())
						, ((GearSprite*)this->getChildByTag(_selectingGear))->getSelectingMapIndex());
		_showMapCover();
		_showLevelCover();
		_showSmlGear();
		_unLockHide();
	}
	else if (_selectingGear == SML_GEAR_IN_LAYER_TAG)
	{
		_showLevelCover();
		_unLockHide();
	}
}

void SelectMapLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void SelectMapLayer::onTouchMoved(Touch* touch, Event* event)
{
	((GearSprite*)this->getChildByTag(_selectingGear))->onTouchMoved(touch, event);
	if (_selectingGear == BIG_GEAR_IN_LAYER_TAG)
	{
		_hideMapCover();
		_hideLevelCover();
		_hideSmlGear();
		_lockHide();
	}

	else if (_selectingGear == SML_GEAR_IN_LAYER_TAG)
	{
		_hideLevelCover();
		_lockHide();
	}
}

///////////////////////////////////////////////////////
//////////////		Layer进出相关	///////////////////
///////////////////////////////////////////////////////
void SelectMapLayer::onEnter(void)
{

	Sprite* big = (Sprite*)this->getChildByTag(BIG_GEAR_IN_LAYER_TAG);
	big->stopAllActions();
	big->setVisible(true);
	big->setOpacity(0);
	big->runAction(Spawn::createWithTwoActions(MoveBy::create(SML_GEAR_MOVE_SPD, Point(big->getContentSize().width*BIG_GEAR_FOR_X, 0))
											, FadeIn::create(SML_GEAR_MOVE_SPD)));
	
	for (auto child : big->getChildren())
	{
		child->runAction(FadeIn::create(SML_GEAR_MOVE_SPD));
		child->setOpacity(0);
	}

	GearSprite* temp = (GearSprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG);
	temp->initWithData(_loadMapDataFromFile((((GearSprite*)big)->getSelectingMapIndex()))
					, ((GearSprite*)big)->getSelectingMapIndex());

	_showMapCover();
	_showLevelCover();
	_showSmlGear();
	Layer::onEnter();
}


/////////////////////////////////

void SelectMapLayer::_showSmlGear(void)
{
	Size _winSize = Director::getInstance()->getWinSize();
	Sprite* sml = (Sprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG);
	if (!_isHide)
		return;

	sml->setVisible(true);
	sml->stopAllActions();
	sml->runAction(Spawn::createWithTwoActions(MoveTo::create(SML_GEAR_MOVE_SPD, Point(_winSize.width*SML_GEAR_FOR_X, _winSize.height*SML_GEAR_FOR_Y))
											, FadeIn::create(SML_GEAR_MOVE_SPD)));
	for (auto child : sml->getChildren())
	{
		child->stopAllActions();
		child->runAction(FadeIn::create(SML_GEAR_MOVE_SPD));
	}
}

void SelectMapLayer::_hideSmlGear(void)
{
	Size _winSize = Director::getInstance()->getWinSize();
	Sprite* sml = (Sprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG);
	if (_isHide)
		return;

	sml->stopAllActions();
	sml->runAction(Spawn::create(MoveTo::create(SML_GEAR_MOVE_SPD, Point(_winSize.width + sml->getContentSize().width*0.5, _winSize.height*SML_GEAR_FOR_Y))
		, FadeOut::create(SML_GEAR_MOVE_SPD)
		, CCCallFuncND::create(this, callfuncND_selector(SelectMapLayer::_setSmlGearVisible), (void*)true)
		, nullptr));
	for (auto child : sml->getChildren())
	{
		child->stopAllActions();
		child->runAction(FadeOut::create(SML_GEAR_MOVE_SPD));
	}
}

void SelectMapLayer::_setSmlGearVisible(cocos2d::Node*, void* flag)
{
	this->getChildByTag(SML_GEAR_IN_LAYER_TAG)->setVisible((bool)flag);
}

int SelectMapLayer::_loadMapDataFromFile(int mapIndex)
{
	int data = _levelData.at(mapIndex) - 'a';
	data = TOOL::Unlock(data);
	return data;
}

void SelectMapLayer::_hideMapCover()
{
	if (_isHide)
		return;
	Size _winSize = Director::getInstance()->getWinSize();
	Sprite* temp = (Sprite*)this->getChildByTag(MAP_COVER_IN_LAYER_TAG);
	temp->stopAllActions();
	temp->runAction(Spawn::createWithTwoActions(
		MoveTo::create(SML_GEAR_MOVE_SPD, Point(temp->getPositionX(), _winSize.height + temp->getContentSize().width*0.5))
		, FadeOut::create(SML_GEAR_MOVE_SPD)));
}

void SelectMapLayer::_showMapCover()
{
	if (!_isHide)
		return;
	Size _winSize = Director::getInstance()->getWinSize();
	String str;
	str.initWithFormat(MAP_COVER_IMAGE_NAME_PATH
		, ((GearSprite*)this->getChildByTag(BIG_GEAR_IN_LAYER_TAG))->getSelectingMapIndex());

	Sprite* mapCover = Sprite::create(str.getCString());
	mapCover->setPosition(mapCover->getContentSize().width*0.5
					, _winSize.height + mapCover->getContentSize().height*0.5);
	this->removeChildByTag(MAP_COVER_IN_LAYER_TAG);
	this->addChild(mapCover, MAP_COVER_IN_LAYER_TAG, MAP_COVER_IN_LAYER_TAG);

	mapCover->stopAllActions();
	mapCover->runAction(Spawn::createWithTwoActions(
		MoveTo::create(SML_GEAR_MOVE_SPD, Point(mapCover->getPositionX(), _winSize.height - mapCover->getContentSize().width*0.5))
		, FadeIn::create(SML_GEAR_MOVE_SPD)));
}

void SelectMapLayer::_hideLevelCover()
{
	if (_isHide)
		return;
	Size _winSize = Director::getInstance()->getWinSize();
	Sprite* temp = (Sprite*)this->getChildByTag(LEVEL_COVER_IN_LAYER_TAG);
	temp->runAction(Spawn::createWithTwoActions(
		MoveTo::create(SML_GEAR_MOVE_SPD, Point(_winSize.width + temp->getContentSize().width*0.5, temp->getPositionY()))
		, FadeOut::create(SML_GEAR_MOVE_SPD)));
}

void SelectMapLayer::_showLevelCover()
{
	if (!_isHide)
		return;
	Size _winSize = Director::getInstance()->getWinSize();
	String str;
	str.initWithFormat(LEVEL_COVER_IMAGE_NAME_PATH
		, ((GearSprite*)this->getChildByTag(BIG_GEAR_IN_LAYER_TAG))->getSelectingMapIndex()
		, ((GearSprite*)this->getChildByTag(SML_GEAR_IN_LAYER_TAG))->getSelectingMapIndex());
	Sprite* levelCover = Sprite::create(str.getCString());
	if (!levelCover)
		return;
	levelCover->setPosition(_winSize.width + levelCover->getContentSize().width*0.5
							, _winSize.height - levelCover->getContentSize().height*0.5);
	this->removeChildByTag(LEVEL_COVER_IN_LAYER_TAG);
	this->addChild(levelCover, LEVEL_COVER_IN_LAYER_TAG, LEVEL_COVER_IN_LAYER_TAG);
	                            
	levelCover->stopAllActions();
	levelCover->runAction(Spawn::createWithTwoActions(
		MoveTo::create(SML_GEAR_MOVE_SPD, Point(_winSize.width - levelCover->getContentSize().width*0.5, levelCover->getPositionY()))
		, FadeIn::create(SML_GEAR_MOVE_SPD)));
}