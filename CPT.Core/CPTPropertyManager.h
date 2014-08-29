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
		注册指定的属性名称和描述，并返回注册的属性对象
	*/
	const PCPTPropertyInfo RegisterProperty(std::string propertyName, std::string description);

	/*
		添加一个属性变化监视器，指定一个监控回调函数，监控的对象类型,返回一个代表该监控实体的
		句柄标志callbackHandle
	*/
	bool AddPropertyChangedObserver(PCPTPropertyCallback pPropertyCallback, UnitType unitType, CPTUINT* callbackHandle);

	/*
		通知一个对象书属性发生变化，该接口仅由AutoPropertyUnit对象或者其子类调用
	*/
	void NotifyPropertyChanged(AutoPropertyUnit* target, PROPERTYKEY key);

	/*
		注销一个确定的监控器
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