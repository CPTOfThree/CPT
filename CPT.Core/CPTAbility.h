#pragma once
#include "CPTBase.h"
#include "cocos2d.h"
#include <list>
USING_NS_CC;
using namespace std;
class CPTAbility
{
public:
	CPTAbility(void);
	~CPTAbility(void);
	CPTBOOL IsEnable;
	void SetAction(Action* action);
	Action* GetAction();
	/*
	virtual void RunAbility();
	virtual void StopAbility();
	*/

private:
	Action* action;
};

