#pragma once

#include "../CPT/CPTBase.h"
#include <fstream>
#include <sstream>
//#include "StartGameScene.h"

class CPTLayoutManager
{ 
public:  
	CPTLayoutManager(CPTINT level);
	~CPTLayoutManager(void);

	//POINTLIST GetAllFriendPositions();

	//CPTPATH CreateEnemyPath();
	void StartScene(Scene* scene);
	void InitLayout(CPTSTRING filePath);
	CPTUnitPath* GetPath(UnitType unitType);
private:
	char* _getFileName(CPTINT level);
	CPTUnitPath* _pathes;
	CPTINT  _pathesCount;
	CPTBOOL _isInit;
};

