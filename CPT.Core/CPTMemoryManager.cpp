#include "CPTMemoryManager.h"


CPTMemoryManager::CPTMemoryManager(void)
{

	// 计算内存片需要消耗的总内存大小，然后分配指定大小的内存块
	// 并且在分配成功后记录下分配的内存大小
	CPTUINT memSliceSize = sizeof(CPTMemorySliceType)* CPTMemoryManager::MAX_MEM_SIZE_TYPE;
	_pMemorySlice = (PCPTMemorySliceType)malloc(memSliceSize);

	if (NULL == _pMemorySlice)
	{
		//分配失败
		goto errors;
	}

	// 记录分配的内存片总大小
	_fixedSizeBySelf += memSliceSize;
	
	// 指定初始值
	CPTUINT blockSize = CPTMemoryManager::MIN_MEM_SLICE_SIZE;
	for (int i = 0; i < CPTMemoryManager::MAX_MEM_SIZE_TYPE; i++)
	{
		(_pMemorySlice[i]).SizeInByte = blockSize;
		(_pMemorySlice[i]).FreeBufferIndex = 0;
		(_pMemorySlice[i]).FreeCount = 0;
		(_pMemorySlice[i]).TotalCount = 0;
		(_pMemorySlice[i]).UsedCount = 0;

		// 增大一倍
		blockSize = (blockSize << 2);
	}

	// 计算内存节点存储对象本身消耗的内存，准备分配。
	CPTUINT bufferSize = sizeof(CPTBufferNode)* CPTMemoryManager::MAX_BUFFER_COUNT;
	_pBuffer = (PCPTBufferNode)malloc(bufferSize);

	if (NULL == _pBuffer)
	{
		// 分配失败
		free(_pMemorySlice);
		goto errors;
	}

	// 记录内存节点消耗的内存大小
	_fixedSizeBySelf     += bufferSize;

	_userAllcatedBytes    = 0;
	_allocatedBufferCount = 0;

	return;

errors:
	// 分配内存失败，严重错误，需要关闭程序
	FatalError(CPT_MEMORY_MANAGER_INITIALIZE_FAILED_FAIL);
}


CPTMemoryManager::~CPTMemoryManager(void)
{
	if (NULL != this->_pMemorySlice)
	{
		free(this->_pMemorySlice);
		this->_pMemorySlice = NULL;
	}

	if (NULL != this->_pBuffer)
	{
		free(this->_pBuffer);
		this->_pBuffer = NULL;
	}
}

//CPTMemoryManager *CPTMemoryManager::GetInstance()
//{
//	if (NULL == CPTMemoryManager::_instance)
//	{
//		CPTMemoryManager::_instance = new CPTMemoryManager;
//	}
//
//	return CPTMemoryManager::_instance;
//}

CPT_RESULT CPTMemoryManager::Alloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo)
{
	CPT_RESULT result = CPT_SUCCESS;

	// 内存不允许超过最大内存片的大小
	if (memBytes > _pMemorySlice[CPTMemoryManager::MAX_MEM_SIZE_TYPE - 1].SizeInByte)
	{
		return CPT_MEMORY_MANAGER_ALLOCATED_TOO_BIT_SIZE;
	}

	// 内存句柄不允许为NULL
	if (NULL == handleInfo)
	{
		return CPT_MEMORY_MANAGER_INVALID_PARAM;
	}

	return this->DoAlloc(memBytes, handleInfo);
}

CPT_RESULT CPTMemoryManager::DoAlloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo)
{
	handleInfo->Index   = 0;
	handleInfo->PAddr   = NULL;
	handleInfo->MemSize = 0;

	CPT_RESULT result = CPT_SUCCESS;

	// 这里需要确定是否需要释放内存，来减小内存压力
	for (CPTINT i = 0; i < CPTMemoryManager::MAX_MEM_SIZE_TYPE; i++)
	{
		if (memBytes <= this->_pMemorySlice[i].SizeInByte)
		{
			// 找到了合适大小的内存块，准备分配内存
			auto memorySlice = _pMemorySlice[i];
			if (0 < memorySlice.FreeCount)
			{
				CPTUINT bufferIndex         = memorySlice.FreeBufferIndex;
				memorySlice.FreeBufferIndex = this->_pBuffer[bufferIndex].NextBufferIndex;

				handleInfo->Index   = bufferIndex;
				handleInfo->MemSize = memorySlice.SizeInByte;
				handleInfo->PAddr   = this->_pBuffer[bufferIndex].Address;

				this->InitBuffer(&this->_pBuffer[bufferIndex]);
				this->MarkAllocated(&this->_pBuffer[bufferIndex]);
				goto allocatedEnd;
			}
			else
			{
				// 没有空闲的内存块，需要重新分配内存
				CPTUINT* pNewAddr = (CPTUINT*)malloc(memorySlice.SizeInByte);

				if (NULL == pNewAddr)
				{
					// 内存分配失败
					result = CPT_MEMORY_MANAGER_MEM_ALLOCATED_FAILED;
					goto allocatedEnd;
				}

				// 统计内存分配
				this->_userAllcatedBytes += memorySlice.SizeInByte;
				memorySlice.TotalCount++;
				memorySlice.FreeCount++;

				this->_pBuffer[this->_allocatedBufferCount].Address = pNewAddr;
				this->_pBuffer[this->_allocatedBufferCount].BufferSizeIndex = i;
				this->ZeroBuffer(pNewAddr, memorySlice.SizeInByte);

				handleInfo->Index   = this->_allocatedBufferCount;
				handleInfo->PAddr   = pNewAddr;
				handleInfo->MemSize = memorySlice.SizeInByte;

				this->_allocatedBufferCount++;
				goto allocatedEnd;
			}
		}
	}

	_CPT_ASSERT(false);

allocatedEnd:
	return result;
}

void CPTMemoryManager::MarkAllocated(PCPTBufferNode pBuffer)
{
	_CPT_ASSERT(pBuffer != NULL);
	_CPT_ASSERT(!pBuffer->IsInUse);
	_CPT_ASSERT(pBuffer->Address != NULL);
	_CPT_ASSERT(pBuffer->AllocatedCount == pBuffer->ReleasedCount);

	this->_pMemorySlice[pBuffer->BufferSizeIndex].FreeCount--;
	this->_pMemorySlice[pBuffer->BufferSizeIndex].UsedCount++;

	pBuffer->AllocatedCount++;
	pBuffer->IsInUse = true;

	_CPT_ASSERT(this->_pMemorySlice[pBuffer->BufferSizeIndex].FreeCount +
				this->_pMemorySlice[pBuffer->BufferSizeIndex].UsedCount ==
				this->_pMemorySlice[pBuffer->BufferSizeIndex].TotalCount);
}

void CPTMemoryManager::InitBuffer(PCPTBufferNode pBuffer)
{
	_CPT_ASSERT(pBuffer != NULL);


}

void CPTMemoryManager::ZeroBuffer(CPTUINT* pBuffer, CPTUINT sizeInBytes)
{

}


