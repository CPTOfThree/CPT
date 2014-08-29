#include "CPTConfigurationManager.h"


CPTConfigurationManager* CPTConfigurationManager::getInstance()
{
	if (_cptConfigurationManager == nullptr)
	{
		_cptConfigurationManager = new CPTConfigurationManager;
	}

	return _cptConfigurationManager;
}

CPTConfigurationManager::CPTConfigurationManager(void)
{

}


CPTConfigurationManager::~CPTConfigurationManager(void)
{
	delete this->_cptConfigurationManager;
}

CPTConfigNode* CPTConfigurationManager::LoadConfig(const CPTSTRING path)
{
	CPTConfigNode* node = new CPTConfigNode;
	auto nodeType = CPTConfigNode::getNodeType(path);
	auto writer = WriterFactory::getWriter(nodeType);
	node->setWriter(writer);
	return node; // ��Path�����ݶ�ȡ����������writer���뵽node�С�
}
