
#include "SelectMapScene.h"
#include "SelectMapLayer.h"

USING_NS_CC;

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
	this->addChild(SelectMapLayer::createWithData(10, 15));
	return true;
}

void SelectMapScene::onEnter()
{
	Scene::onEnter();
}
