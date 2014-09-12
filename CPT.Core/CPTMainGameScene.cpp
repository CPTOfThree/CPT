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
	// ���ص�ǰ�ؿ��µı���ͼ
	//auto level = CPTRTLevelInfo::getRTLevelInfo(false)->level;
	auto backgroundLayer = Layer::create();
	this->addChild(backgroundLayer);

	// �������Ϸ��
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