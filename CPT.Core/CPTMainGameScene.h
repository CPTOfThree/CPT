#pragma once
#include "CPTBase.h"
#include "Log.h"
#include "BackgroundLayer.h"
#include "CPTEnemyUnit.h"
#include "MainGameLayer.h"
#include "CPTLayoutManager.h"
#include "CPTEnemyUnit.h"
#include "CPTRTLevelInfo.h"
#include <stdlib.h>
class CPTMainGameScene : public Scene
{
public:
	CREATE_FUNC(CPTMainGameScene);
	~CPTMainGameScene(void);
	CPTLayoutManager* layoutManager;
	virtual bool init();
	virtual void loadGameLayers();
	void addEnemy(CPTEnemyUnit* enemyUnit);
	void timeToAddEnemy(CPTFLOAT dt);
	void onAttach(CPTFLOAT x, CPTFLOAT y);
};

