/**************************************************************************************************************
 author : ÷‹ºŒΩ‡
 date   : 2014-9-6
 All Rights Reserved 
*************************************************************************************************************/

#pragma once
#include "CPTBase.h"
#include "AutoPropertyUnit.h"
#include "cocos2d.h"
#include <list>
#include "CPTAbility.h"
USING_NS_CC;
class CPTEnemyUnit : public AutoPropertyUnit
{
public:
	CPTEnemyUnit(Sprite* node);
	~CPTEnemyUnit(void);
	Sprite* GetNode();
	CPTBOOL IsHit(CPTFLOAT x, CPTFLOAT y);
	UnitType GetUnitType();
	void AddAbility(CPTAbility* ability);
	void RunAbilities();

private:
	Sprite* node;
	UnitType _unitType;
	list<CPTAbility*>* abilities;
};

