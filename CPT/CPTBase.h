#include "vld.h"
#ifndef _CPT_BASE_H_
#define _CPT_BASE_H_

#define DEBUG

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UILayout.h" 
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

/*
	基础类型定义
*/
#define CPTLONG     long
#define CPTUINT     unsigned int
#define CPTINT      int
#define CPTFLOAT    float
#define CPTBOOL     bool
#define CPTULONG    unsigned long
#define CPTBYTE     char
#define CPTSTRING   std::string

#define CPT_PROPERTY_KEY CPTINT
#define CPT_PROPERTY_VALUE CPTFLOAT

/*
	当前版本属性 常量定义
*/
#define MAX_SUPPORT_PROPERTY_NUM 64
#define ATTACK_PROPERTY          0
#define DEFENSE_PROPERTY         1
#define LIFE_PROPERTY            2

#define CPTPATH Vector<Vec2&>
#define POINTLIST Vector<Vec2&>


#define CPT_START_GAME_SCENE_PATH "res/StartGame/StartGame.json"
#define CPT_SELECT_LEVEL_SCENE_PATH "res/SelectLevel/SelectLevel.json"
#define CPT_START_GAME_BTN "btnStartGame"
#define CPT_CONTINUE_GAME_BTN "btnContinueGame"

/* 
	定义通用的程序返回错误码
*/
#define CPT_RESULT CPTULONG
#define CPT_SUCCESS                                 0x0000000000000000
#define CPT_MEMORY_MANAGER_INITIALIZE_FAILED_FAIL   0x0000000000000001
#define CPT_MEMORY_MANAGER_ALLOCATED_TOO_BIT_SIZE   0x0000000000000002
#define CPT_MEMORY_MANAGER_INVALID_PARAM            0x0000000000000004
#define CPT_MEMORY_MANAGER_MEM_ALLOCATED_FAILED     0x0000000000000008
#define CPT_PROPERTY_MANAGER_INITIALIZE_FIALED_FAIL 0x0000000000000010
#define CPT_PROPERTY_MANAGER_REGISTER_NULL_NAME     0x0000000000000020
#define CPT_PROPERTY_MANAGER_NAME_EXIST             0x0000000000000040
#define CPT_PROPERTY_MANAGER_OUT_OF_MAX_COUNT       0x0000000000000080


#define CPTLoadLayoutFromPath(path) dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance() \
									->widgetFromJsonFile(path))
#define CPTFindControlByName(layout,name,type) static_cast<type*>(Helper::seekWidgetByName(\
									layout,name)) 
#define CPTMakeTEvent(callback)     toucheventselector(callback)
//#define CPTMakeTEvent(callback)     SEL_TouchEvent(callback)

#ifdef DEBUG

#define _CPT_INITIALIZE_FLAG_FIELD CPTBOOL _initSuccessfully
#define _CPT_ASSERT_VALID_STATE   _CPT_ASSERT(this->_initSuccessfully)
#define _CPT_INITIALIZE_SUCCESS    this->_initSuccessfully = true
#define _CPT_INITIALIZE_FAIL       this->_initSuccessfully = false
#else
#define _CPT_INITIALIZE_FLAG_FIELD CPTBOOL
#define _CPT_ASSERT_VALID_STATE
#define _CPT_INITIALIZE_SUCCESS
#define _CPT_INITIALIZE_FAIL
#endif

#define _CPTFatalError(p)        return

#define _CPT_NO_CONTRACT
#define _CPT_ASSERT_M(cond,message)
#define _CPT_ASSERT(cond)         _CPT_ASSERT_M(cond,NULL)
#define _CPT_ASSERT_NOT_NULL(OBJ) _CPT_ASSERT(NULL != (OBJ))
#define _CPT_ASSERT_UI_THREAD
enum UnitType
{
	Enemy,
	Friend,
	Player
} ;

class CPTPoint
{
private:
	CPTINT x;
	CPTINT y;
public:
	inline CPTINT getX() const{ return this->x; }
	inline CPTINT getY() const{ return this->y; }
	void setX(CPTINT x){ this->x = x; }
	void setY(CPTINT y){ this->y = y; }
};

typedef struct cptUnitPath
{
	UnitType unitType;
	CPTPoint *points;
	int length;
} CPTUnitPath;
#endif