#include "CPTPlayController.h"

/*
	定时触发函数
*/
/*void CALLBACK CPTPlayController::TimeProc(HWND hWnd, UINT nMSG, UINT nTimerId, DWORD dwTime)
{
	//_CPT_Log("1");
	// 添加怪物
	CPTEnemyUnit* unit = new CPTEnemyUnit(Sprite::create());
	this->mainGameScene->addEnemy(unit);
}
*/


void CALLBACK TimeProc(HWND hWnd, UINT nMSG, UINT nTimerid, DWORD dwTime)
{
	//_CPT_Log("1");
	// 添加怪物
	
	CPTEnemyUnit* unit = new CPTEnemyUnit(Sprite::create());
	//this->mainGameScene->addEnemy(unit);
	
}

CPTPlayController::CPTPlayController(void)
{

}


CPTPlayController::~CPTPlayController(void)
{
}

void CPTPlayController::StartPlay()
{

	SetTimer(NULL, 1, 1000, TimeProc); //
	// 监听点击事件
	//mainGameScene->schedule(schedule_selector(CPTPlayController::AddEnemy), 1.0f);
}

void CPTPlayController::AddEnemy(CPTFLOAT dt)
{
}

void CPTPlayController::PausePlay()
{
	
}

