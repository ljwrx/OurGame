#include "SelectLayer.h"

SelectLayer::SelectLayer()
{

}

SelectLayer::~SelectLayer()
{

}

bool SelectLayer::initWithData(int data, int canSel)
{
	return true;
}

SelectLayer* SelectLayer::createWithData(int data, int canSel)
{
	SelectLayer* pRet = new SelectLayer();
	if (pRet || pRet->initWithData(data, canSel))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}