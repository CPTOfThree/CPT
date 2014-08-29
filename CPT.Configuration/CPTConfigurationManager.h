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
	* 装载指定的配置文件到内存
	* @path 配置文件的全路径名
	*/
	CPTConfigNode* LoadConfig(const CPTSTRING path);

private:
	CPTConfigurationManager(void);

	static CPTConfigurationManager* _cptConfigurationManager;
};

