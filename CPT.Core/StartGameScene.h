#include "CPTBase.h"

#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__


class StartGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartGame);

private:
	// �����ʼ��Ϸ�˵��ص�
    void buttonStartGameCallback(Ref* target,TouchEventType touchType);
    
	// ���������Ϸ�˵��ص�
	void buttonContinueGameCallBack(cocos2d::Ref* pSender, TouchEventType touchType);

};

#endif // __HELLOWORLD_SCENE_H__
