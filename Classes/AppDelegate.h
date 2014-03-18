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
��˽�м̳�ʵ����Ϊ�����ط��ʵ�ĳЩ�ӿ�
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
	ʵ�ֹ��ܺͳ�����ʼ������������
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
	��ʼ��ʧ�ܣ�Ӧ����ֹ
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
	Ӧ�ó�����ʾ������ʱ�򷵻صķ���
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
	Ӧ�ó�����ʾǰ����ʱ�򷵻صķ���
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

