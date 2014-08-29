#include "CPTPropertyManager.h"

CPTPropertyManager::CPTPropertyManager(void)
{
	_CPT_ASSERT_UI_THREAD;

	// ��ʼ�����Թ�����
	PCPTPropertyInfo pPropertyInfo = (PCPTPropertyInfo)malloc(sizeof(CPTPropertyInfo)* CPTPropertyManager::MAX_PROPERTY_COUNT);

	if (NULL == pPropertyInfo)
	{
		// ��ʼ��ʧ��
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

	// ������������Ƿ�Ϊ�գ�������ע��һ��û�����Ƶ�����
	if (propertyName.empty())
	{
		result = CPT_PROPERTY_MANAGER_REGISTER_NULL_NAME;
		goto endReg;
	}

	// ����Ƿ������Ѿ���ע��
	for (int i = 0; i < this->_registeredCount; i++)
	{
		if (0 == propertyName.compare(this->_properties[i].PropertyName))
		{
			// �����Ѿ�����
			result = CPT_PROPERTY_MANAGER_NAME_EXIST;
			goto endReg;
		}
	}

	// ������Ը����Ƿ񳬹����ֵ
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





