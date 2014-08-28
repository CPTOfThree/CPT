#pragma once

#ifndef _CPT_PROPERTY_MANAGER_H_
#define _CPT_PROPERTY_MANAGER_H_
#include "CPTBase.h"
#include "AutoPropertyUnit.h"

typedef void CPTPROPERTYCALLBACK(AutoPropertyUnit *target, PROPERTYKEY propertyKey);
typedef CPTPROPERTYCALLBACK* PCPTPropertyCallback;

typedef struct CPTPropertyInfo{
	
}* PCPTPropertyInfo;



class PropertyManager
{
public:
	PropertyManager(void);
	~PropertyManager(void);

	/*
		ע��ָ�����������ƺ�������������ע������Զ���
	*/
	PCPTPropertyInfo RegisterProperty(std::string propertyName, std::string description);

	/*
		���һ�����Ա仯��������ָ��һ����ػص���������صĶ�������,����һ������ü��ʵ���
		�����־callbackHandle
	*/
	bool AddPropertyChangedObserver(PCPTPropertyCallback pPropertyCallback, UnitType unitType, CPTUINT* callbackHandle);

	/*
		֪ͨһ�����������Է����仯���ýӿڽ���AutoPropertyUnit����������������
	*/
	void NotifyPropertyChanged(AutoPropertyUnit* target, PROPERTYKEY key);

	/*
		ע��һ��ȷ���ļ����
	*/
	bool RemovePropertyChangedObserver(UnitType unitType, CPTUINT callbackHandle);

private:
	static const CPTUINT MAX_PROPERTY_COUNT = 128;

	PCPTPropertyInfo _properties;
};

#endif