#ifndef _CPT_RT_LEVEL_INFO_
#define _CPT_RT_LEVEL_INFO_
#include "../CPT/CPTBase.h"
#include <list>
#include "CPTFriendUnit.h"
#include "CPTEnemyUnit.h"

//#include "CPTLayoutManager.h"
using namespace std;

// 使用该类代表当前关卡的信息
class CPTRTLevelInfo
{
public:
	static CPTRTLevelInfo* getRTLevelInfo(CPTBOOL needNew);
	~CPTRTLevelInfo(void);
	list<CPTFriendUnit*>* GetFirends();
	list<CPTEnemyUnit*>* GetEnemys();
	void AddEnemy(CPTEnemyUnit* unit);
	CPTFriendUnit* HitTestFirend(CPTFLOAT x, CPTFLOAT y);
	CPTEnemyUnit* HitTestEnemys(CPTFLOAT x, CPTFLOAT y);
	CPTBOOL AddDeadEnemy(CPTEnemyUnit* unit);
	CPTINT level;
	//CPTMainGameScene* mainGameScene;

private:
	CPTRTLevelInfo(void);
	CPTRTLevelInfo(CPTRTLevelInfo& info);
	static CPTRTLevelInfo* _self;
	list<CPTFriendUnit*>* firends;
	list<CPTEnemyUnit*>* enemys;
	list<CPTEnemyUnit*>* deadEnemys;
};


#endif

