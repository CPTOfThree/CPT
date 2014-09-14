#pragma once
#include "CPTBase.h"
#include "CPTAbility.h"
#include "RandomWalkAbility.h"
class AbilityFactory
{
public:
	AbilityFactory(void);
	~AbilityFactory(void);
	static CPTAbility* GetAbility(CPTAbilityType type);
};

