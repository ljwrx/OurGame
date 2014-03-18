#include "SelectSprite.h"

SelectSprite::SelectSprite()
{
}

SelectSprite::~SelectSprite()
{
}

void SelectSprite::_setImageFromData(int a,bool b)
{

}

bool SelectSprite::init(const std::string& filename, int data)
{
	if (!ScissorSpriteNode::initWithFile(filename))
		return false;

}

SelectSprite* SelectSprite::create(const std::string& filename, int data)
{
	SelectSprite *sprite = new SelectSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

