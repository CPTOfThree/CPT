#pragma once

#include "CPTConfigNode.h"
#include "ConfigBase.h"
#include "WriterFactory.h"

class CPTConfigurationManager
{
public:
	static CPTConfigurationManager* getInstance();

	~CPTConfigurationManager(void);

	/*
	* װ��ָ���������ļ����ڴ�
	* @path �����ļ���ȫ·����
	*/
	CPTConfigNode* LoadConfig(const CPTSTRING path);

private:
	CPTConfigurationManager(void);

	static CPTConfigurationManager* _cptConfigurationManager;
};

