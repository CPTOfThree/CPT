#include "CPTAbility.h"


CPTAbility::CPTAbility(void)
{
	this->IsEnable = false;
}


CPTAbility::~CPTAbility(void)
{
}

void CPTAbility::SetAction(Action* action)
{
	this->action = action;
}

Action* CPTAbility:: GetAction()
{
	return this->action;
}