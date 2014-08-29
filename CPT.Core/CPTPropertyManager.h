#pragma once

#ifndef _CPT_PROPERTY_MANAGER_H_
#define _CPT_PROPERTY_MANAGER_H_
#include "../CPT/CPTBase.h"
#include "AutoPropertyUnit.h"

typedef void CPTPROPERTYCALLBACK(AutoPropertyUnit *target, CPTUINT propertyIndex);

typedef CPTPROPERTYCALLBACK* PCPTPropertyCallback;


typedef std::list<PCPTPropertyCallback> CallBackList,* PCallBackList;

typedef struct CPTPropertyInfo{
	CPTUINT   ProperyIndex;
	CPTSTRING PropertyName;
	CPTSTRING Descrption;
	PCallBackList pCallbackList;
}* PCPTPropertyInfo;

class CPTPropertyManager
{
public:
	/*
		ע��ָ�����������ƺ�������������ע������Զ���
	*/
	CPT_RESULT RegisterProperty(CPTSTRING propertyName, CPTSTRING description, PCPTPropertyInfo* pCPTPropertyInfo);

	/*
		���һ�����Ա仯��������ָ��һ����ػص���������صĶ�������,����һ������ü��ʵ���
		�����־callbackHandle
	*/
	CPT_RESULT AddPropertyChangedObserver(PCPTPropertyCallback pPropertyCallback, UnitType unitType, CPTUINT* callbackHandle);

	/*
		֪ͨһ�����������Է����仯���ýӿڽ���AutoPropertyUnit����������������
	*/
	void NotifyPropertyChanged(AutoPropertyUnit* target, PROPERTYKEY key);

	/*
		ע��һ��ȷ���ļ����
	*/
	CPT_RESULT RemovePropertyChangedObserver(UnitType unitType, CPTUINT callbackHandle);


private:

	_CPT_INITIALIZE_FLAG_FIELD;

	CPTPropertyManager(void);
	~CPTPropertyManager(void);

	static const CPTUINT MAX_PROPERTY_COUNT = 128;
	static CPTPropertyManager* _instance;

	PCPTPropertyInfo _properties;
	CPTUINT          _registeredCount;

	CPT_RESULT DoRegisterProperty(CPTSTRING propertyName, CPTSTRING description, PCPTPropertyInfo* pPCPTPropertyInfo);
};

#endif