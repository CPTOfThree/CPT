#include "CPTBase.h"

#pragma once
class AutoPropertyUnit
{
public:
	AutoPropertyUnit(void);
	~AutoPropertyUnit(void);

	/*
		Ϊ��ǰ��������ָ��������ֵ
	*/
	void SetProperty(CPT_PROPERTY_KEY proIndex, CPT_PROPERTY_VALUE value);
	CPT_PROPERTY_VALUE GetProperty(CPT_PROPERTY_KEY proIndex);
};

