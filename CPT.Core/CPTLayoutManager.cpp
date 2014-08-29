#include "CPTLayoutManager.h"


CPTLayoutManager::CPTLayoutManager(CPTINT level)
{ 
	//CPTLayoutManager::InitLayout();  
	//this->_isInit = false;
	// 读取对应level的地图，并将其替换现有的Scene
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
			// 这里处理有两种：1.对于一大片区域根据路径算法生成一串路径返回
			// 2.保存的时候就已经分好路径，直接返回其中一条
			return &(*_pathes);
		}
	}
}

void CPTLayoutManager::InitLayout(CPTSTRING filePath)
{
	// 解析该目录下的地图位置文件
	// 分不同的unitType和pathType类解析
	/*
	if (this->_isInit == true)
	{
		return;
	}

	this->_isInit = true;
	*/

	// 通过ConfigurationManager获取到当前关卡的路径数据
	// 存到_pathes中
	int tempCount = 3;  // 这里的数字将从ConfigurationManager中获取
	_pathes = (CPTUnitPath*)malloc(tempCount*sizeof(CPTUnitPath)); // 说明有3条路径
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