#include "ScissorSpriteNode.h"
USING_NS_CC;
ScissorSpriteNode::ScissorSpriteNode()
{

}

ScissorSpriteNode::~ScissorSpriteNode()
{

}

ScissorSpriteNode* ScissorSpriteNode::createWithTexture(Texture2D *texture)
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

ScissorSpriteNode* ScissorSpriteNode::createWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (sprite && sprite->initWithTexture(texture, rect, rotated))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

ScissorSpriteNode* ScissorSpriteNode::create(const std::string& filename)
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

ScissorSpriteNode* ScissorSpriteNode::create(const std::string& filename, const Rect& rect)
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

ScissorSpriteNode* ScissorSpriteNode::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

ScissorSpriteNode* ScissorSpriteNode::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}

ScissorSpriteNode* ScissorSpriteNode::create()
{
	ScissorSpriteNode *sprite = new ScissorSpriteNode();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void ScissorSpriteNode::visit()
{
	glEnable(GL_SCISSOR_TEST);//这句启用纹理裁剪

	//这里要根据CCNode 的位置 和父类的大小 来计算具体的裁剪区域
	Point pos = this->getPosition();
	Size size = this->getContentSize();
	glScissor(pos.x, pos.y, size.width - 5, size.height - 5);//x, y, w, h 

	Node::visit();//调用自己的类方法
	glDisable(GL_SCISSOR_TEST);//管理纹理裁剪
}