#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	//动态载入标题文字图片
    //auto topsprite = Sprite::create("top.png"); 
    //addChild(topsprite, 0); 
    //topsprite->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 50)); 
	//topsprite->

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	auto size = Director::sharedDirector()->getWinSize();

	auto pStartLabel = LabelTTF::create("Start Game","Arial",30);
	auto pExitLabel = LabelTTF::create("Exit Game","Arial",30);
	auto pAboutLabel = LabelTTF::create("About Game","Arial",30);
    
	MenuItemLabel *pStartItem = MenuItemLabel::create(pStartLabel,this,menu_selector(HelloWorld::startGameCallback));
	MenuItemLabel *pExitItem = MenuItemLabel::create(pExitLabel,this,menu_selector(HelloWorld::exitGameCallback));
	MenuItemLabel *pAboutItem = MenuItemLabel::create(pAboutLabel,this,menu_selector(HelloWorld::aboutGameCallback));

	Menu *pStartMenu = Menu::create(pStartItem,NULL);
	Menu *pExitMenu = Menu::create(pExitItem, NULL); 
    Menu *pAboutMenu = Menu::create(pAboutItem, NULL); 

	pStartItem->setPosition(Point(size.width / 2, size.height / 2 + 50)); 
    pExitItem->setPosition(Point(size.width / 2, size.height / 2  - 50 )); 
    pAboutItem->setPosition(Point(size.width / 2, size.height / 2 )); 
 
    pStartMenu->setPosition(CCPointZero); 
    pExitMenu->setPosition(CCPointZero); 
    pAboutMenu->setPosition(CCPointZero); 
 
    addChild(pStartMenu, 2); 
    addChild(pExitMenu, 2); 
    addChild(pAboutMenu, 2); 

	//添加背景 
    auto sprite = Sprite::create("HelloWorld.png"); 
    addChild(sprite, 0); 
    sprite->setPosition(Point(size.width / 2, size.height / 2)); 
 
    //添加动画 
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bear.plist"); 
	SpriteBatchNode* spritesheet = SpriteBatchNode::create("bear.png"); 
 
	addChild(spritesheet, 1);

    Vector<SpriteFrame *> animFrames; 
    char str[20]; 
    for (int i=1; i<=6; i++) 
    { 
        sprintf(str, "bear%d.png", i); 
		animFrames.insert(i-1,SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str)) ;
    } 
 
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f); 

	Sprite *bear = Sprite::createWithSpriteFrameName("bear1.png");
	bear->setPosition(ccp(size.width / 2, size.height / 2));

    ActionInterval* walkAction = RepeatForever::create(Animate::create(animation)); 
    bear->runAction(walkAction); 
	spritesheet->addChild(bear);
 
    //熊运动轨迹 
    //ActionInterval* move1 = MoveBy::create(3,Point(size.width / 4, size.height / 4)); 
    //ActionInterval* move1_back = move1->reverse(); 
    //ActionInterval* move2 = MoveBy::create(3,Point(size.width / 4, -size.height / 4)); 
    //ActionInterval* move2_back = move2->reverse(); 
    //spritesheet->runAction(RepeatForever::create((ActionInterval*)(Sequence::create(move1, move1,move2,move2, move2_back,move2_back,move1_back,move1_back, NULL)))); 

} 
 

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

 
void HelloWorld::aboutGameCallback(Object* pSender) 
{ 
    Size size = Director::sharedDirector()->getWinSize(); 
 
    //显示关于的内容 
    LabelTTF* label = LabelTTF::create("Made by LJW", "Arial", 30); 
    label->setPosition(Point(size.width / 2, size.height / 2)); 
    Scene* s = Scene::create(); 
    Layer* layer = Layer::create(); 
    layer->addChild(label, 1); 
 
    //返回按钮 
    LabelTTF* pBackLabel = LabelTTF::create("Back", "Arial", 30); 
    MenuItemLabel* pBackItem = MenuItemLabel::create(pBackLabel, this, menu_selector(HelloWorld::backGameCallback)); 
    Menu* pBackMenu = Menu::create(pBackItem, NULL); 
    pBackItem->setPosition(Point(size.width  - 50, 50)); 
    pBackMenu->setPosition(CCPointZero); 
    layer->addChild(pBackMenu, 1); 
 
    s->addChild(layer); 
 
    Director::sharedDirector()->replaceScene(s); 
    //s->release(); 
    //layer->release(); 
 
} 
 
void HelloWorld::startGameCallback(Object* pSender) 
{ 
    //跳转到游戏中 
	Scene* scene = Scene::create(); 
    Layer* layer = new HelloWorld(); 
    scene->addChild(layer); 
    Director::sharedDirector()->replaceScene(scene); 
    scene->release(); 
    layer->release(); 
} 
 
 
void HelloWorld::exitGameCallback(Object* pSender) 
{ 
    Director::sharedDirector()->end(); 
} 
 
void HelloWorld::backGameCallback(Object* pSender) 
{ 
    Size size= Director::sharedDirector()->getWinSize(); 
    //跳转到游戏中 
    Scene* scene = Scene::create(); 
    Layer* layer = new HelloWorld(); 
    scene->addChild(layer); 
    Director::sharedDirector()->replaceScene(scene); 
    scene->release(); 
    layer->release(); 

} 
 
void HelloWorld::onEnter() 
{ 
    Layer::onEnter(); 
} 
