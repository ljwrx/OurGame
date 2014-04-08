#include "scrollView.h"

USING_NS_CC;

#define SCROLLVIEW_WIDTH	1152
#define SCROLLVIEW_HEIGHT	1536
#define DIALOGMESSAGE_X		87
#define DIALOGMESSAGE_Y		1266

scrollView* scrollView::create(void)
{
	scrollView *sv = new scrollView();
	if (sv && sv->init())
	{
		sv->setTouchEnabled(true);
		sv->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sv);
	}

    return sv;
}

bool scrollView::init()
{
	if ( !LayerColor::initWithColor(ccc4(255,255,255,255),SCROLLVIEW_WIDTH,SCROLLVIEW_HEIGHT) )
    {
        return false;
    }

	isDialog = false;

	auto spritelistener = EventListenerTouchOneByOne::create();
	spritelistener->setSwallowTouches(true);
	spritelistener->onTouchBegan = CC_CALLBACK_2(scrollView::onSpriteTouchBegan,this);
	spritelistener->onTouchMoved = CC_CALLBACK_2(scrollView::onSpriteTouchMoved,this);
	spritelistener->onTouchEnded = CC_CALLBACK_2(scrollView::onSpriteTouchEnded,this);

	int n = 45;
	Sprite *sp;
	sp = Sprite::create("saber.png");
	this->addChild(sp,1,1);
	sp->setPosition(32,1436);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener,this->getChildByTag(1));

	for (int i = 1; i < n; i++)
	{
		sp = Sprite::create("saber.png");
		this->addChild(sp,1,i+1);
		sp->setPosition(32+i%4*85,1536-(i/4+1)*100);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener->clone(),this->getChildByTag(i+1));
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(scrollView::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(scrollView::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(scrollView::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	xvel = 0.0f;
	acceleration = 0.0f;

    return true;
}

scrollView::scrollView()
{
}

scrollView::~scrollView()
{
}

void scrollView::update(float dt)
{
	if (!isDragging && m_moveInstancySpeed != 0)
	{
		layerLocationY = getPositionY();
		acceleration = isPositive*96*dt;
		xvel += acceleration;

		if ((m_moveInstancySpeed > 0 && xvel <= 0) || (m_moveInstancySpeed < 0 && xvel >= 0))
		{
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
			return;
		}

		layerLocationY += xvel*dt;

		if (layerLocationY < -1024)
		{
			layerLocationY = -1024;
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
		}
		else if (layerLocationY > 0)
		{
			layerLocationY = 0;
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
		}

		setPositionY(layerLocationY);
	}
}

bool scrollView::onTouchBegan(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		Point touchPosition = pTouch->getLocation();
		Rect rect = Rect(87,242,210,210);

		//点击范围判断检测
		if (!rect.containsPoint(touchPosition))
		{
			this->getChildByTag(0)->setOpacity(0);
			this->getChildByTag(0)->setZOrder(0);
			this->getChildByTag(0)->removeChildByTag(1);
			return true;
		}
		return false;
	}
	m_touchDownPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	m_firstTouchPointX = m_touchDownPoint.x;
	m_firstTouchPointY = m_touchDownPoint.y;

	m_touchCurPoint = m_touchDownPoint;
	isClip = true;
	isDragging = true;
	isPositive = 0;
	xvel = 0.0f;
	acceleration = 0.0f;
	m_moveInstancySpeed = 0.0f;

	stopAllActions();
	return true;
}

void scrollView::onTouchMoved(Touch *pTouch,Event *pEvent)
{
	isClip = false;

	if (isDialog)
	{
		return;
	}

	touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());

	m_moveDisplaceY = touchPoint.y - m_touchCurPoint.y;

	if (m_moveDisplaceY > 0)
	{
		isMoveUp = false;
		isPositive = -1;
	}else
	{
		isMoveUp = true;
		isPositive = 1;
	}

	if (getPositionY() + m_moveDisplaceY < -1024)
	{
		setPosition(getPositionX(),-1024);
	}else if (getPositionY() + m_moveDisplaceY > 0)
	{
		setPosition(getPositionX(),0);
	}else
	{
		setPosition(getPositionX(),getPositionY() + m_moveDisplaceY);
	}
	
	m_moveInstancySpeed = m_moveDisplaceY * 60;
	xvel = m_moveInstancySpeed;
	//m_moveToStopTime = m_moveInstancySpeed / 100;

	m_touchCurPoint = touchPoint;
}

void scrollView::onTouchEnded(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		isDialog = false;
		return;
	}

	m_lastTouchPontX = Director::getInstance()->convertToGL(pTouch->getLocationInView()).x;
	m_lastTouchPontY = Director::getInstance()->convertToGL(pTouch->getLocationInView()).y;

	if (fabsf(m_lastTouchPontX-m_firstTouchPointX) >= fabsf(m_lastTouchPontY-m_firstTouchPointY))
	{
		m_moveInstancySpeed = 0;
		if (m_lastTouchPontX-m_firstTouchPointX >= 96)
		{
			moveX = MoveTo::create(1.0f,Point::Point(getPositionX()+384,getPositionY()));
			runAction(moveX);
			return;
		}else if (m_lastTouchPontX-m_firstTouchPointX < -96)
		{
			moveX = MoveTo::create(0.5f,Point::Point(getPositionX()-384,getPositionY()));
			runAction(moveX);
			return;
		}
	}

	isDragging = false;
}

void scrollView::onEnter()
{
	LayerColor::onEnter();
	scheduleUpdate();
	isMoveUp = false;
	isPositive = 1;
	isDragging = true;

	LayerColor *ObscurationLayer = LayerColor::create(ccc4(0,0,0,200),SCROLLVIEW_WIDTH,SCROLLVIEW_HEIGHT);
	ObscurationLayer->setOpacity(0);

	addChild(ObscurationLayer,0,0);
	ObscurationLayer->setPosition(CCPointZero);

}

void scrollView::onExit()
{
	unscheduleUpdate();
	removeAllChildrenWithCleanup(true);
	_eventDispatcher->removeAllEventListeners();
	LayerColor::onExit();
}

bool scrollView::onSpriteTouchBegan(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return false;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	//获取当前点击点所在的相对按钮的位置坐标
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();

	Rect rect = Rect(0,0,s.width,s.height);

	//点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("success draw x = %f,y = %f",locationInNode.x,locationInNode.y);
		target->setOpacity(180);
		return true;
	}
	return false;
}

void scrollView::onSpriteTouchMoved(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	//移动当前按钮精灵的坐标位置
	target->setPosition(target->getPosition() + pTouch->getDelta());
}

void scrollView::onSpriteTouchEnded(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	log("sprite onTouchesEnded.. ");
	target->setOpacity(255);

	DialogMessage *dm = DialogMessage::create();
	dm->initDialog("saber.png","saber");
	target->getParent()->getChildByTag(0)->addChild(dm,1,1);
	dm->setAnchorPoint(Point::ZERO);
	dm->setPosition(dm->getParent()->convertTouchToNodeSpace(pTouch));
	dm->setScale(0.01);
	FiniteTimeAction *action1 = ScaleBy::create(2, 100);
	FiniteTimeAction *action2 = FadeIn::create(2);
	FiniteTimeAction *action3 = MoveTo::create(2,ccp(DIALOGMESSAGE_X,256-getPositionY()));
	dm->runAction(Spawn::create(action1,action2,action3,NULL));

	target->getParent()->getChildByTag(0)->setOpacity(180);
	target->getParent()->getChildByTag(0)->setZOrder(2);

	isDialog = true;

}
