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
	glEnable(GL_SCISSOR_TEST);//�����������ü�

	//����Ҫ����CCNode ��λ�� �͸���Ĵ�С ���������Ĳü�����
	Point pos = this->getPosition();
	Size size = this->getContentSize();
	glScissor(pos.x, pos.y, size.width, size.height);//x, y, w, h 

	Node::visit();//�����Լ����෽��
	glDisable(GL_SCISSOR_TEST);//��������ü�
}