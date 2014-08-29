#include "CPTMemoryManager.h"


CPTMemoryManager::CPTMemoryManager(void)
{
	// �����ڴ�Ƭ��Ҫ���ĵ����ڴ��С��Ȼ�����ָ����С���ڴ��
	// �����ڷ���ɹ����¼�·�����ڴ��С
	CPTUINT memSliceSize = sizeof(CPTMemorySliceType)* CPTMemoryManager::MAX_MEM_SIZE_TYPE;
	_pMemorySlice = (PCPTMemorySliceType)malloc(memSliceSize);

	if (NULL == _pMemorySlice)
	{
		//����ʧ��
		goto errors;
	}

	// ��¼������ڴ�Ƭ�ܴ�С
	_fixedSizeBySelf += memSliceSize;
	
	// ָ����ʼֵ
	CPTUINT blockSize = CPTMemoryManager::MIN_MEM_SLICE_SIZE;
	for (int i = 0; i < CPTMemoryManager::MAX_MEM_SIZE_TYPE; i++)
	{
		(_pMemorySlice[i]).SizeInByte      = blockSize;
		(_pMemorySlice[i]).FreeBufferIndex = 0;
		(_pMemorySlice[i]).FreeCount       = 0;
		(_pMemorySlice[i]).TotalCount      = 0;
		(_pMemorySlice[i]).UsedCount       = 0;

		// ����һ��
		blockSize = (blockSize << 2);
		_CPT_ASSERT(blockSize > 0);    // ȷ���ڴ��Сû�����
	}

	// �����ڴ�ڵ�洢���������ĵ��ڴ棬׼�����䡣
	CPTUINT bufferSize = sizeof(CPTBufferNode)* CPTMemoryManager::MAX_BUFFER_COUNT;
	_pBuffer = (PCPTBufferNode)malloc(bufferSize);

	if (NULL == _pBuffer)
	{
		// ����ʧ��
		goto errors;
	}

	// ��¼�ڴ�ڵ����ĵ��ڴ��С
	_fixedSizeBySelf     += bufferSize;

	_userAllcatedBytes    = 0;
	_allocatedBufferCount = 0;
	
	_CPT_INITIALIZE_SUCCESS;
	return;

errors:
	_CPT_INITIALIZE_FAIL;

	if (NULL != this->_pMemorySlice)
	{
		free(_pMemorySlice);
		_pMemorySlice = NULL;
	}

	if (NULL != this->_pBuffer)
	{
		free(_pBuffer);
		_pBuffer = NULL;
	}

	// �����ڴ�ʧ�ܣ����ش�����Ҫ�رճ���
	_CPTFatalError(CPT_MEMORY_MANAGER_INITIALIZE_FAILED_FAIL);
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
//
//CPTMemoryManager *CPTMemoryManager::GetInstance()
//{
//	if (NULL == _instance)
//	{
//		_instance = new CPTMemoryManager();
//	}
//
//	return _instance;
//}

CPT_RESULT CPTMemoryManager::Alloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo)
{
	CPT_RESULT result = CPT_SUCCESS;

	// �ڴ治����������ڴ�Ƭ�Ĵ�С
	if (memBytes > _pMemorySlice[CPTMemoryManager::MAX_MEM_SIZE_TYPE - 1].SizeInByte)
	{
		return CPT_MEMORY_MANAGER_ALLOCATED_TOO_BIT_SIZE;
	}

	// �ڴ���������ΪNULL
	if (NULL == handleInfo)
	{
		return CPT_MEMORY_MANAGER_INVALID_PARAM;
	}

	return this->DoAlloc(memBytes, handleInfo);
}

CPT_RESULT CPTMemoryManager::DoAlloc(CPTUINT memBytes, PCPTMemoryHandle handleInfo)
{
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT_NOT_NULL(handleInfo);

	handleInfo->Index   = 0;
	handleInfo->PAddr   = NULL;
	handleInfo->MemSize = 0;

	CPT_RESULT result = CPT_SUCCESS;

	// ������Ҫȷ���Ƿ���Ҫ�ͷ��ڴ棬����С�ڴ�ѹ��
	for (CPTINT i = 0; i < CPTMemoryManager::MAX_MEM_SIZE_TYPE; i++)
	{
		if (memBytes <= this->_pMemorySlice[i].SizeInByte)
		{
			// �ҵ��˺��ʴ�С���ڴ�飬׼�������ڴ�
			auto memorySlice = _pMemorySlice[i];
			if (0 < memorySlice.FreeCount)
			{
				CPTUINT bufferIndex = memorySlice.FreeBufferIndex;
				
				result = this->InitBuffer(&this->_pBuffer[bufferIndex]);

				if (CPT_SUCCESS != result)
				{
					//��ʼ�������ڴ�ʧ�ܣ�ֱ�ӷ���
					goto allocatedEnd;
				}

				memorySlice.FreeBufferIndex = this->_pBuffer[bufferIndex].NextBufferIndex;

				handleInfo->Index   = bufferIndex;
				handleInfo->MemSize = memorySlice.SizeInByte;
				handleInfo->PAddr   = this->_pBuffer[bufferIndex].Address;

				this->MarkAllocated(&this->_pBuffer[bufferIndex]);
				goto allocatedEnd;
			}
			else
			{
				// û�п��е��ڴ�飬��Ҫ���·����ڴ�
				CPTUINT* pNewAddr = (CPTUINT*)malloc(memorySlice.SizeInByte);

				if (NULL == pNewAddr)
				{
					// �ڴ����ʧ��
					result = CPT_MEMORY_MANAGER_MEM_ALLOCATED_FAILED;
					goto allocatedEnd;
				}

				// ͳ���ڴ����
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
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT_NOT_NULL(pBuffer != NULL);
	_CPT_ASSERT(!pBuffer->IsInUse);
	_CPT_ASSERT_NOT_NULL(pBuffer->Address != NULL);
	_CPT_ASSERT(pBuffer->AllocatedCount == pBuffer->ReleasedCount);

	this->_pMemorySlice[pBuffer->BufferSizeIndex].FreeCount--;
	this->_pMemorySlice[pBuffer->BufferSizeIndex].UsedCount++;

	pBuffer->AllocatedCount++;
	pBuffer->IsInUse = true;

	_CPT_ASSERT(this->_pMemorySlice[pBuffer->BufferSizeIndex].FreeCount +
				this->_pMemorySlice[pBuffer->BufferSizeIndex].UsedCount ==
				this->_pMemorySlice[pBuffer->BufferSizeIndex].TotalCount);
}

CPT_RESULT CPTMemoryManager::InitBuffer(PCPTBufferNode pBuffer)
{
	_CPT_ASSERT(pBuffer != NULL);

	CPTUINT bufferSize = this->_pMemorySlice[pBuffer->BufferSizeIndex].SizeInByte;

	if (NULL == pBuffer->Address)
	{
		// ��ַ�Ѿ����ͷţ���Ҫ���·���
		CPTUINT* pNewAddr = (CPTUINT*)malloc(bufferSize);

		if (NULL == pNewAddr)
		{
			// �ڴ����ʧ��
			return CPT_MEMORY_MANAGER_MEM_ALLOCATED_FAILED;
		}

		this->_userAllcatedBytes += bufferSize;
		pBuffer->Address = pNewAddr;
	}

	_CPT_ASSERT_NOT_NULL(pBuffer->Address);

	this->ZeroBuffer(pBuffer->Address, bufferSize);

	return CPT_SUCCESS;
}

void CPTMemoryManager::ZeroBuffer(const CPTUINT* pBuffer,const CPTUINT sizeInBytes)
{
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT_NOT_NULL(pBuffer);
	_CPT_ASSERT(sizeInBytes > 0);

	CPTBYTE* pbBuffer = (CPTBYTE*)pBuffer;
	CPTUINT  index    = 0;
	CPTUINT  bufferLength = sizeInBytes;

	while (bufferLength > 4)
	{
		*(pbBuffer + index + 0) = 0;
		*(pbBuffer + index + 1) = 0;
		*(pbBuffer + index + 2) = 0;
		*(pbBuffer + index + 3) = 0;
		index        += 4;
		bufferLength -= 4;
	}

	while (bufferLength > 0)
	{
		*(pbBuffer + index) = 0;
		index++;
		bufferLength++;
	}

	_CPT_ASSERT(0     == bufferLength);
	_CPT_ASSERT(index == sizeInBytes);
}

CPT_RESULT CPTMemoryManager::Free(CPTUINT index)
{
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT(index < this->_allocatedBufferCount);

	this->MarkFree(&this->_pBuffer[index]);

	CPTUINT memSliceIndex = this->_pBuffer[index].BufferSizeIndex;

	_CPT_ASSERT(memSliceIndex < CPTMemoryManager::MAX_MEM_SIZE_TYPE);

#define MAX_HOLD_MEMSLICE_SIZE        2000000
#define MAX_HOLD_MEMSLICE_FREE_COUNT  10

	PCPTMemorySliceType pMemSliceType = &this->_pMemorySlice[memSliceIndex];
	if (pMemSliceType->FreeCount > MAX_HOLD_MEMSLICE_FREE_COUNT &&
		pMemSliceType->FreeCount * pMemSliceType->SizeInByte > MAX_HOLD_MEMSLICE_SIZE)
	{
		// ֱ���ͷ��ڴ�
		free(this->_pBuffer[index].Address);

		this->_userReleasedBytes += pMemSliceType->SizeInByte;
		this->_userAllcatedBytes -= pMemSliceType->SizeInByte;
		this->_pBuffer[index].Address = NULL;
	}

	// �������ڴ������б�ʼλ��
	this->_pBuffer[index].NextBufferIndex = pMemSliceType->FreeBufferIndex;
	pMemSliceType->FreeBufferIndex        = index;

	return CPT_SUCCESS;
}

void CPTMemoryManager:: MarkFree(PCPTBufferNode pBuffer)
{
	_CPT_ASSERT_VALID_STATE;
	_CPT_ASSERT_NOT_NULL(pBuffer);
	_CPT_ASSERT_NOT_NULL(pBuffer->Address);
	_CPT_ASSERT(pBuffer->IsInUse);

	PCPTMemorySliceType pMemSliceType = &this->_pMemorySlice[pBuffer->BufferSizeIndex];

	pMemSliceType->FreeCount++;
	pMemSliceType->UsedCount--;
	pBuffer->IsInUse = FALSE;
	pBuffer->ReleasedCount++;

	_CPT_ASSERT(pBuffer->AllocatedCount == pBuffer->ReleasedCount);
	_CPT_ASSERT(pMemSliceType->FreeCount + pMemSliceType->UsedCount == pMemSliceType->TotalCount);
}
