#include "CPTBase.h"

#pragma once
class AutoPropertyUnit
{
public:
	AutoPropertyUnit(void);
	~AutoPropertyUnit(void);

	/*
		为当前对象设置指定的属性值
	*/
	void SetProperty(CPT_PROPERTY_KEY proIndex, CPT_PROPERTY_VALUE value);
	CPT_PROPERTY_VALUE GetProperty(CPT_PROPERTY_KEY proIndex);
};

