/**************************************************************************************************************
 author : ÷‹ºŒΩ‡
 date   : 2014-9-6
 All Rights Reserved 
*************************************************************************************************************/

#pragma once
#include "CPTBase.h"
#include "cocos2d.h"
#include "AutoPropertyUnit.h"
USING_NS_CC;

class CPTFriendUnit : public AutoPropertyUnit
{
public:
	CPTFriendUnit(Sprite* node);
	~CPTFriendUnit(void);
	Sprite* GetNode();
	CPTBOOL IsHit(CPTFLOAT x, CPTFLOAT y);
	UnitType GetUnitType();

private:
	Sprite* node;
	UnitType _unitType;
};

