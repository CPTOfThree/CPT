#include "CPTLayoutManager.h"


CPTLayoutManager::CPTLayoutManager(CPTINT level)
{ 
	//CPTLayoutManager::InitLayout();  
	//this->_isInit = false;
	// ��ȡ��Ӧlevel�ĵ�ͼ���������滻���е�Scene
	auto fileName = this->_getFileName(level);
	auto scene = dynamic_cast<Scene*>(CPTLoadLayoutFromPath(fileName));
	CCDirector::getInstance()->replaceScene(scene);
}

CPTLayoutManager::~CPTLayoutManager(void)
{
}

char* CPTLayoutManager::_getFileName(CPTINT level)
{
	/*
	char* map = "map/";
	char* json = ".json";
	char* buf = (char*)malloc(strlen(map)+strlen(json)+1);
	strcat(buf, map);
	strcat(buf, level + "");
	strcat(buf, json);
	delete map;
	delete json;
	*/
	/*
	int aa;
	int* a = &aa;
	std::stringstream s = std::stringstream();
	std::stringstream * pS =  &s;*/

	std::stringstream stream;
	stream.clear();
	stream << "map/" << level << ".json";
	char* result = "";
	stream >> result;
	return result;
}

CPTUnitPath* CPTLayoutManager::GetPath(UnitType unitType)
{
	for (auto i = 0; i < _pathesCount; i++)
	{
		auto path = _pathes[i];
		if (path.unitType == unitType)
		{
			// ���ﴦ�������֣�1.����һ��Ƭ�������·���㷨����һ��·������
			// 2.�����ʱ����Ѿ��ֺ�·����ֱ�ӷ�������һ��
			return &(*_pathes);
		}
	}
}

void CPTLayoutManager::InitLayout(CPTSTRING filePath)
{
	// ������Ŀ¼�µĵ�ͼλ���ļ�
	// �ֲ�ͬ��unitType��pathType�����
	/*
	if (this->_isInit == true)
	{
		return;
	}

	this->_isInit = true;
	*/

	// ͨ��ConfigurationManager��ȡ����ǰ�ؿ���·������
	// �浽_pathes��
	int tempCount = 3;  // ��������ֽ���ConfigurationManager�л�ȡ
	_pathes = (CPTUnitPath*)malloc(tempCount*sizeof(CPTUnitPath)); // ˵����3��·��
	_pathesCount = tempCount;
	for (auto i = 0; i < _pathesCount; i++)
	{
		int tempCount2 = 0;
		switch (i)
		{
		case 1:
			tempCount2 = 100;
			_pathes->points = (CPTPoint*)malloc(tempCount2*sizeof(CPTPoint)); //
			_pathes->length = tempCount2;
			_pathes->unitType = UnitType::Enemy;
			break;
		case 2:
			tempCount2 = 50;
			_pathes->points = (CPTPoint*)malloc(tempCount2*sizeof(CPTPoint)); //
			_pathes->length = tempCount2;
			_pathes->unitType = UnitType::Player;
			break;
		case 3:
			tempCount2 = 7;
			_pathes->points = (CPTPoint*)malloc(tempCount2*sizeof(CPTPoint)); //
			_pathes->length = tempCount2;
			_pathes->unitType = UnitType::Friend;
			break;
		default:
			break;
		}
	}
}