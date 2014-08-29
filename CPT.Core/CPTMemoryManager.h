#include "CPTBase.h"

#ifndef _CPT_MEMORY_MANAGER_H_
#define _CPT_MEMORY_MANAGER_H_


/*
	������ڴ���Ϣ�ṹ�壬�������ڴ��Ӧ�ľ����������ʼ��ַ�Լ�
	���ڴ��ľ���Ĵ�С�ֽ�����
*/
typedef struct CPTMemoryHandle
{
	CPTUINT Index;
	CPTUINT *PAddr;
	CPTUINT MemSize;
} *PCPTMemoryHandle;


/*
	�ڴ������Ϣ�ṹ�壬������ǰ�ڴ��ʹ������������
	�ֶε�ʱ�������Ҫ�ٽ������ġ�
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
		��ȡ�ڴ��������Ψһʵ��
	*/
	static CPTMemoryManager* GetInstance();

	/*
		ʹ�øýӿڷ���ָ����С���ڴ�飬���ظ��ڴ���Ӧ�ľ����Ϣ
	*/
	CPT_RESULT Alloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo);

	/*
		�ͷŵ�ǰ������ڴ�������
	*/
	CPT_RESULT Free(CPTUINT index);

	/*
		��ָ�����ڴ�����������
	*/
	CPT_RESULT Clear(CPTUINT index);

	/*
		��ȡ��ǰ����ʱ�ڴ�������Ϣ������������Ժͷ�����ǰ�ڴ��ʹ��״��
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