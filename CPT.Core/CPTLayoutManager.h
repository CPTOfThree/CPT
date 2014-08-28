#pragma once

#include "CPTBase.h"
#include <fstream>
#include <sstream>

class CPTLayoutManager
{ 
public:  
	CPTLayoutManager(int level);
	~CPTLayoutManager(void);

	//POINTLIST GetAllFriendPositions();

	//CPTPATH CreateEnemyPath();
	void StartScene(Scene* scene);
	void InitLayout(char* filePath);
	CPTUnitPath* GetPath(UnitType unitType);
private:
	char* _getFileName(int level);
	CPTUnitPath* _pathes;
	int  _pathesCount;
	bool _isInit;
};

