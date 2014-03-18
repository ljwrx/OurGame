#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};
#endif // __HELLOWORLD_SCENE_H__


/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
用私有继承实现是为了隐藏访问的某些接口
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
	实现功能和场景初始化代码在这里
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
	初始化失败，应用终止
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
	应用程序显示背景的时候返回的方法
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
	应用程序显示前景的时候返回的方法
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

