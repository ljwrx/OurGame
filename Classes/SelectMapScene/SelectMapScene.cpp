
#include "SelectMapScene.h"

USING_NS_CC;

#define BIF_GEAR_FOR_X			0.029
#define BIF_GEAR_FOR_Y			0.5
#define SML_GEAR_FOR_X			0.9
#define SML_GEAR_FOR_Y			0.42

#define BG_IN_LAYER_TAG			0
#define BIG_GEAR_IN_LAYER_TAG	1
#define SML_GEAR_IN_LAYER_TAG	2
#define MAP_FILE_NAME_PATH		"save//mapdata.txt"


SelectMapScene::SelectMapScene()
{

}
SelectMapScene::~SelectMapScene()
{

}

bool SelectMapScene::init()
{
	if (!Scene::init())
		return false;
	int _mapData = _checkMapCanSelFromFile();
	Size _winSize = Director::getInstance()->getWinSize();

	Layer* layer = Layer::create();
	layer->setAnchorPoint(Point(0, 0));
	layer->setPosition(Point::ZERO);

	Sprite* bg = Sprite::create("res\\SelevtMapRec\\BG.png");
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);
	layer->addChild(bg, BG_IN_LAYER_TAG, BG_IN_LAYER_TAG);

	Sprite* gear = Sprite::create("res\\SelevtMapRec\\big_gear.png");
	gear->setPosition(_winSize.width*BIF_GEAR_FOR_X, _winSize.height*BIF_GEAR_FOR_Y);
	layer->addChild(gear, BIG_GEAR_IN_LAYER_TAG, BIG_GEAR_IN_LAYER_TAG);

	gear = Sprite::create("res\\SelevtMapRec\\sml_gear.png");
	gear->setPosition(_winSize.width*SML_GEAR_FOR_X, _winSize.height*SML_GEAR_FOR_Y);
	layer->addChild(gear, SML_GEAR_IN_LAYER_TAG, SML_GEAR_IN_LAYER_TAG);

	this->addChild(layer, 0, 0);
	return true;
}

void SelectMapScene::onEnter()
{
	Scene::onEnter();
	Layer* layer = (Layer*)(this->getChildByTag(0));
	RotateBy* rotateby = RotateBy::create(5, 360);
	layer->getChildByTag(BIG_GEAR_IN_LAYER_TAG)->runAction(RepeatForever::create(rotateby));
	layer->getChildByTag(SML_GEAR_IN_LAYER_TAG)->runAction(RepeatForever::create(rotateby->reverse()));
}

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
int SelectMapScene::_checkMapCanSelFromFile()
{
	String str = FileUtils::getInstance()->getStringFromFile(MAP_FILE_NAME_PATH);
	return str.intValue();
}
short int SelectMapScene::_checkMapDataFromFile(int no)
{
	return 0;
}