#include "../CPT/CPTBase.h"

#ifndef _SELECT_LEVEL_SCENE_
#define _SELECT_LEVEL_SCENE_

#define CPT_SELECT_LEVEL_BUTTON_NAME_1 "btnLevel1"
#define CPT_SELECT_LEVEL_BUTTON_NAME_2 "btnLevel2"
#define CPT_SELECT_LEVEL_BUTTON_NAME_3 "btnLevel3"
#define CPT_SELECT_LEVEL_BUTTON_NAME_4 "btnLevel4"
#define CPT_SELECT_LEVEL_BUTTON_NAME_5 "btnLevel5"
#define CPT_SELECT_LEVEL_BUTTON_NAME_6 "btnLevel6"

class SelectLevel : cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(SelectLevel);

private:

	// 点击开始游戏菜单回调
    void selectLevelCallback(Ref* target,TouchEventType touchType);
};

#endif