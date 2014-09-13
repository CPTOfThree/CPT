#include "CPTRTLevelInfo.h"
//CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::getRTLevelInfo(bool needNew)
{
	if (needNew == true 
		|| _self == nullptr
		)
	{
		_self = new CPTRTLevelInfo();
	}

	return _self;
	//static CPTRTLevelInfo instance;   //局部静态变量
	
	return _self;
}

CPTRTLevelInfo::~CPTRTLevelInfo(void)
{
	
}

CPTRTLevelInfo::CPTRTLevelInfo(void)
{
	
}

list<CPTEnemyUnit>* CPTRTLevelInfo::GetEnemys()
{
	return this->enemys;
}

list<CPTFirendUnit*>* CPTRTLevelInfo::GetFirends()
{
	return this->firends;
}

CPTFirendUnit* CPTRTLevelInfo::HitTestFirend(CPTFLOAT x, CPTFLOAT y)
{
	CPTFirendUnit* unit = NULL;
	for (auto iter = this->firends->begin(); iter != this->firends->end(); iter++)
	{
		if ((*iter)->IsHit(x, y))
		{
			unit = (*iter);
		}
	}
	
	return unit;
}

CPTEnemyUnit* CPTRTLevelInfo::HitTestEnemys(CPTFLOAT x, CPTFLOAT y)
{
	CPTEnemyUnit* unit = NULL;
	for (auto iter = this->enemys->begin(); iter != this->enemys->end(); iter++)
	{
		if ((iter)->IsHit(x, y))
		{
			unit = (&(*iter));
		}
	}
	return unit;
}

void CPTRTLevelInfo::AddEnemy(CPTEnemyUnit* unit)
{
	//this->enemys->push_back((&unit));
	this->enemys->push_back(*unit);
}