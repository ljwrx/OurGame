#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ItemMoveSprite.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "CocosGUI.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
	void onEnter(); 

    void startGameCallback(Object* pSender); 
    void aboutGameCallback(Object* pSender); 
    void exitGameCallback(Object* pSender); 
    void backGameCallback(Object* pSender); 

	void sceneChange(Object* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	gui::Layout *m_layout;
};

#endif // __HELLOWORLD_SCENE_H__
