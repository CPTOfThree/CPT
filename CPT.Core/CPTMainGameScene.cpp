#include "CPTMainGameScene.h"

CPTMainGameScene::~CPTMainGameScene(void)
{
}

bool CPTMainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}

void CPTMainGameScene::loadGameLayers()
{
	// 加载当前关卡下的背景图
	//auto level = CPTRTLevelInfo::getRTLevelInfo(false)->level;
	auto backgroundLayer = Layer::create();
	this->addChild(backgroundLayer);

	// 添加主游戏层
	auto mainGameLayer = (Layer*)MainGameLayer::create();
	this->addChild(mainGameLayer);
}

void CPTMainGameScene::addEnemy(CPTEnemyUnit* enemyUnit)
{
	this->addChild(enemyUnit->GetNode());
}

void CPTMainGameScene::onAttach(CPTFLOAT x, CPTFLOAT y)
{
	auto rtLevelInfo = CPTRTLevelInfo::getRTLevelInfo();
}