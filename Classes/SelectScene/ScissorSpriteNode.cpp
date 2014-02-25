#include "ScissorSpriteNode.h"
USING_NS_CC;
ScissorSpriteNode::ScissorSpriteNode()
{

}

ScissorSpriteNode::~ScissorSpriteNode()
{

}

void ScissorSpriteNode::visit()
{
	glEnable(GL_SCISSOR_TEST);//这句启用纹理裁剪

	//这里要根据CCNode 的位置 和父类的大小 来计算具体的裁剪区域
	Point pos = this->getPosition();
	Size size = this->getContentSize();
	glScissor(pos.x, pos.y, size.width, size.height);//x, y, w, h 

	Node::visit();//调用自己的类方法
	glDisable(GL_SCISSOR_TEST);//管理纹理裁剪
}