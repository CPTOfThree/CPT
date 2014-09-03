#pragma once
#include "cocos2d.h"
#include "TouchLayer.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	~GameScene(void);
};

