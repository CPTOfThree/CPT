#include "GameScene.h"

bool GameScene::init()
{
	if (Scene::init()){
		TouchLayer* touchLayer = TouchLayer::create();
		this->addChild(touchLayer);
	}

	return true;
}


GameScene::~GameScene(void)
{
}
