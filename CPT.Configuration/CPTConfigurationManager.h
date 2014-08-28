#pragma once
#include "CPTConfigNode.h"
#include "ConfigBase.h"
#include "WriterFactory.h"
class CPTConfigurationManager
{
public:
	static CPTConfigurationManager* getInstance();
	~CPTConfigurationManager(void);
	CPTConfigNode* loadConfig(char* path);

private:
	CPTConfigurationManager(void);
	static CPTConfigurationManager* _cptConfigurationManager;
};

