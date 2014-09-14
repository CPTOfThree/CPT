#include "AbilityFactory.h"


AbilityFactory::AbilityFactory(void)
{
}


AbilityFactory::~AbilityFactory(void)
{
}

CPTAbility* AbilityFactory::GetAbility(CPTAbilityType type)
{
	CPTAbility* ability = NULL;
	switch (type)
	{
	case CPTAbilityType::Default:
		ability = new CPTAbility;
		break;
	case CPTAbilityType::GoStraightWalk:
		break;
	case CPTAbilityType::RandomWalk:
		ability = new RandomWalkAbility;
		break;
	default:
		break;
	}

	return ability;
}