#include "CPTRTLevelInfo.h"
//CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::getRTLevelInfo(bool needNew)
{
	/*
	if (needNew == true 
		|| _self == nullptr
		)
	{
		_self = new CPTRTLevelInfo();
	}

	return _self;
	*/
	return NULL;
}

CPTRTLevelInfo::~CPTRTLevelInfo()
{
	
}

list<CPTEnemyUnit*>* CPTRTLevelInfo::GetEnemys()
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
		if ((*iter)->IsHit(x, y))
		{
			unit = (*iter);
		}
	}
	
	return unit;
}