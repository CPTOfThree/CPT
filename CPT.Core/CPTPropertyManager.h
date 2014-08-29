#pragma once

#ifndef _CPT_PROPERTY_MANAGER_H_
#define _CPT_PROPERTY_MANAGER_H_
#include "CPTBase.h"
#include "AutoPropertyUnit.h"

typedef void CPTPROPERTYCALLBACK(AutoPropertyUnit *target, CPTUINT propertyIndex);

typedef CPTPROPERTYCALLBACK* PCPTPropertyCallback;

typedef struct CPTPropertyInfo{
	CPTUINT   ProperyIndex;
	CPTSTRING PropertyName;
	CPTSTRING Descrption;
	PCallBackList pCallbackList;
}* PCPTPropertyInfo;

typedef std::list<PCPTPropertyCallback> CallBackList,* PCallBackList;

class CPTPropertyManager
{
public:
	/*
		ע��ָ�����������ƺ�������������ע������Զ���
	*/
	const PCPTPropertyInfo RegisterProperty(std::string propertyName, std::string description);

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
	CPTPropertyManager(void);
	~CPTPropertyManager(void);

	static const CPTUINT MAX_PROPERTY_COUNT = 128;
	static CPTPropertyManager* _instance;

	PCPTPropertyInfo _properties;
};

#endif