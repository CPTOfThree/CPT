#include "CPTBase.h"

#ifndef _CPT_MEMORY_MANAGER_H_
#define _CPT_MEMORY_MANAGER_H_


/*
	定义的内存信息结构体，包括该内存对应的句柄索引，开始地址以及
	该内存块的具体的大小字节数。
*/
typedef struct CPTMemoryHandle
{
	CPTUINT Index;
	CPTUINT *PAddr;
	CPTUINT MemSize;
} *PCPTMemoryHandle;


/*
	内存诊断信息结构体，包含当前内存的使用情况，具体的
	字段到时候根据需要再进行增改。
*/
typedef struct CPTMemoryDiagnosisInfo
{
	CPTLONG Total;
	CPTUINT Alive;
} *PCPTMemoryDiagnosisInfo;


typedef struct CPTBufferNode 
{
	CPTUINT NextBufferIndex;
	CPTUINT BufferSizeIndex;

	CPTINT  AllocatedCount;
	CPTINT  ReleasedCount;
	CPTBOOL IsInUse;

	CPTUINT* Address;
}*PCPTBufferNode;

typedef struct CPTMemorySliceType
{
	CPTUINT SizeInByte;
	CPTUINT FreeBufferIndex;

	CPTUINT FreeCount;
	CPTUINT TotalCount;
	CPTUINT UsedCount;
}*PCPTMemorySliceType;

class CPTMemoryManager
{
	public:

	/*
		获取内存管理器的唯一实例
	*/
	static CPTMemoryManager* GetInstance();

	/*
		使用该接口分配指定大小的内存块，返回该内存块对应的句柄信息
	*/
	CPT_RESULT Alloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo);

	/*
		释放当前分配的内存索引块
	*/
	CPT_RESULT Free(CPTUINT index);

	/*
		将指定的内存索引块清零
	*/
	CPT_RESULT Clear(CPTUINT index);

	/*
		获取当前运行时内存的诊断信息，用于软件调试和分析当前内存的使用状况
	*/
	CPT_RESULT GetMemoryDiagnosis(PCPTMemoryDiagnosisInfo pMemDiagInfo);

private:
	static CPTMemoryManager* _instance;

	static const CPTUINT  MAX_MEM_SIZE_TYPE = 20;
	static const CPTUINT  MAX_BUFFER_COUNT = 10000;
	static const CPTUINT  MAX_ALLOC_BYTES_LIMIT = 100000000;
	static const CPTUINT  MIN_MEM_SLICE_SIZE = 16;

	CPTUINT  _fixedSizeBySelf;
	CPTUINT  _userAllcatedBytes;
	CPTUINT  _userReleasedBytes;
	CPTUINT  _allocatedBufferCount;

	_CPT_INITIALIZE_FLAG_FIELD;

	PCPTBufferNode      _pBuffer;
	PCPTMemorySliceType _pMemorySlice;

	CPTMemoryManager(void);
	~CPTMemoryManager(void);

	inline CPT_RESULT DoAlloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo);
	inline CPT_RESULT InitBuffer(PCPTBufferNode pBuffer);
	inline void       MarkAllocated(PCPTBufferNode pBuffer);
	inline void       MarkFree(PCPTBufferNode pBuffer);
	inline void       ZeroBuffer(const CPTUINT* pBuffer,const CPTUINT sizeInBytes);
};

#endif