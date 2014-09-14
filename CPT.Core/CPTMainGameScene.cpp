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

	this->schedule(schedule_selector(CPTMainGameScene::timeup), 0.0f);
	this->listener = EventListenerTouchOneByOne::create();
	this->listener->onTouchBegan = CC_CALLBACK_2(CPTMainGameScene::OnTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(this->listener, this);
	return true;
}

void CPTMainGameScene::timeup(CPTFLOAT dt)
{
	this->timeToAddEnemy(dt);
}

void CPTMainGameScene::timeToAddEnemy(CPTFLOAT dt)
{
	auto sprite = Sprite::create("Target.png");
	auto enemy = new CPTEnemyUnit(sprite);
	this->addEnemy(enemy);
}

CPTBOOL CPTMainGameScene::OnTouch(Touch* touch, Event  *event)
{
	auto location = touch->getLocation();
	//this->onAttach(e->getCursorX(), e->getCursorY());
	this->onAttach(location.x, location.y);
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
	auto levelInfo = CPTRTLevelInfo::getRTLevelInfo(false);
	levelInfo->AddEnemy(enemyUnit);
	auto path = layoutManager->GetPath(UnitType::Enemy);

	auto point = path->points[0];
	enemyUnit->GetNode()->setPosition(point.getX(), point.getY());
	auto time = 3 + (rand() % 10);
	auto action = MoveTo::create(time, Point(point.getX(), 0));
	//enemyUnit->GetNode()->runAction(action);
	auto ability = AbilityFactory::GetAbility(CPTAbilityType::Default);
	ability->SetAction(action);
	ability->IsEnable = true;
	enemyUnit->AddAbility(ability);
	enemyUnit->RunAbilities();
	this->addChild(enemyUnit->GetNode());
}

void CPTMainGameScene::onAttach(CPTFLOAT x, CPTFLOAT y)
{
	auto rtLevelInfo = CPTRTLevelInfo::getRTLevelInfo(false);
	AutoPropertyUnit* obj = rtLevelInfo->HitTestEnemys(x, y);
	if (obj != nullptr)
	{
		//delete obj;
		rtLevelInfo->AddDeadEnemy((CPTEnemyUnit*)obj);
	}
}