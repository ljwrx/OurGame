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
	glEnable(GL_SCISSOR_TEST);//�����������ü�

	//����Ҫ����CCNode ��λ�� �͸���Ĵ�С ���������Ĳü�����
	Point pos = this->getPosition();
	Size size = this->getContentSize();
	glScissor(pos.x, pos.y, size.width - 5, size.height - 5);//x, y, w, h 

	Node::visit();//�����Լ����෽��
	glDisable(GL_SCISSOR_TEST);//��������ü�
}