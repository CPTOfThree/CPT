#include "CPTPropertyManager.h"

CPTPropertyManager::CPTPropertyManager(void)
{
	_CPT_ASSERT_UI_THREAD;

	// 初始化属性管理器
	PCPTPropertyInfo pPropertyInfo = (PCPTPropertyInfo)malloc(sizeof(CPTPropertyInfo)* CPTPropertyManager::MAX_PROPERTY_COUNT);

	if (NULL == pPropertyInfo)
	{
		// 初始化失败
		_CPT_INITIALIZE_FAIL;
		_CPTFatalError(CPT_PROPERTY_MANAGER_INITIALIZE_FIALED_FAIL);
	}

	_CPT_INITIALIZE_SUCCESS;
	this->_registeredCount = 0;
	this->_properties      = pPropertyInfo;

	return;
}

CPTPropertyManager::~CPTPropertyManager(void)
{
}

CPT_RESULT CPTPropertyManager::RegisterProperty(CPTSTRING propertyName, CPTSTRING description, PCPTPropertyInfo* pPCPTPropertyInfo)
{
	_CPT_ASSERT_UI_THREAD;
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT(!propertyName.empty());
	_CPT_ASSERT_NOT_NULL(pPCPTPropertyInfo);

	CPT_RESULT result = CPT_SUCCESS;

	// 继续检查名称是否为空，不允许注册一个没有名称的属性
	if (propertyName.empty())
	{
		result = CPT_PROPERTY_MANAGER_REGISTER_NULL_NAME;
		goto endReg;
	}

	// 检查是否名称已经被注册
	for (int i = 0; i < this->_registeredCount; i++)
	{
		if (0 == propertyName.compare(this->_properties[i].PropertyName))
		{
			// 名称已经存在
			result = CPT_PROPERTY_MANAGER_NAME_EXIST;
			goto endReg;
		}
	}

	// 检查属性个数是否超过最大值
	if (this->_registeredCount >= CPTPropertyManager::MAX_PROPERTY_COUNT)
	{
		result = CPT_PROPERTY_MANAGER_OUT_OF_MAX_COUNT;
		goto endReg;
	}

	result = this->DoRegisterProperty(propertyName, description, pPCPTPropertyInfo);
endReg:
	return result;
}

CPT_RESULT CPTPropertyManager::DoRegisterProperty(CPTSTRING propertyName, CPTSTRING description, PCPTPropertyInfo* pPCPTPropertyInfo)
{
	_CPT_NO_CONTRACT;

	this->_properties[this->_registeredCount].PropertyName = propertyName;
	this->_properties[this->_registeredCount].Descrption   = description;
	this->_properties[this->_registeredCount].ProperyIndex = this->_registeredCount;

	*pPCPTPropertyInfo = &this->_properties[this->_registeredCount];
	this->_registeredCount++;
	return CPT_SUCCESS;
}





