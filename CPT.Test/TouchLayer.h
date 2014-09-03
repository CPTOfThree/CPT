#pragma once
#include <vector>
#include "cocos2d.h"
#include "GameScene.h"
using namespace std;
USING_NS_CC;
class TouchLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(TouchLayer);
	~TouchLayer(void);

	bool init();
    void onTouchBegan(const std::vector<Touch*>& touches, cocos2d::Event* event);  
	void onTouchMoved(const std::vector<Touch*>& touches, cocos2d::Event* event);  
	void onTouchEnded(const std::vector<Touch*>& touches, cocos2d::Event* event);  
	void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

    //开启、关闭触摸的接口
    void setTouchEnabled(bool flag);

protected:
    //GameScene* getGameScene();
    //cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *touch);
};

