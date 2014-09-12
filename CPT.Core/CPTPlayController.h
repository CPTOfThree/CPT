#pragma once
#include "CPTBase.h"
#include "CPTRTLevelInfo.h"
#include "CPTMainGameScene.h"
#include <time.h>
#include "Log.h"
#include "CPTEnemyUnit.h"
#include "minwindef.h"

class CPTPlayController
{
public:
	CPTPlayController(void);
	~CPTPlayController(void);

	void StartPlay();
	void StopPlay();
	void PausePlay();
	void RestartPlay();
	//friend void CALLBACK TimeProc(HWND hWnd, UINT nMSG, UINT nTimerId, DWORD dwTime);
	CPTMainGameScene* mainGameScene;
};

