#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene : public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	~GameScene(void);
};

