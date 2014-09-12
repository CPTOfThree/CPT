#pragma once
#include "CPTBase.h"
#include "BackgroundLayer.h"
#include "CPTEnemyUnit.h"
#include "MainGameLayer.h"
class CPTMainGameScene : public Scene
{
public:
	CREATE_FUNC(CPTMainGameScene);
	~CPTMainGameScene(void);

	virtual bool init();
	virtual void loadGameLayers();
	void addEnemy(CPTEnemyUnit* enemyUnit);
};

