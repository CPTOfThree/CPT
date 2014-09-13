#include "CPTRTLevelInfo.h"
//CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::_self = NULL;
CPTRTLevelInfo* CPTRTLevelInfo::getRTLevelInfo(bool needNew)
{
	if (needNew == true || _self == nullptr)
	{
		_self = new CPTRTLevelInfo();
	}

	return _self;
	//static CPTRTLevelInfo instance;   //�ֲ���̬����
	
	return _self;
}

CPTRTLevelInfo::~CPTRTLevelInfo(void)
{
	delete this->enemys;
	delete this->friends;
}

CPTRTLevelInfo::CPTRTLevelInfo(void)
{
	this->enemys = new list<CPTEnemyUnit*>;
	this->friends = new list<CPTFriendUnit*>;
	this->deadEnemys = new list<CPTEnemyUnit*>;
}

list<CPTEnemyUnit*>* CPTRTLevelInfo::GetEnemys()
{
	return this->enemys;
}

list<CPTFriendUnit*>* CPTRTLevelInfo::GetFirends()
{
	return this->friends;
}

CPTFriendUnit* CPTRTLevelInfo::HitTestFirend(CPTFLOAT x, CPTFLOAT y)
{
	CPTFriendUnit* unit = NULL;
	for (auto iter = this->friends->begin(); iter != this->friends->end(); iter++)
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

CPTBOOL CPTRTLevelInfo::AddDeadEnemy(CPTEnemyUnit* unit)
{
	unit->GetNode()->setVisible(false);
	this->enemys->remove(unit);
	this->deadEnemys->push_back(unit);
	return true;
}

void CPTRTLevelInfo::AddEnemy(CPTEnemyUnit* unit)
{
	//this->enemys->push_back((&unit));
	this->enemys->push_back(unit);
}