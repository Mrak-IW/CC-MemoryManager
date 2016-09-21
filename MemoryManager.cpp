#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned char *memPtr, int bufferSize, int memoryAlignment):
	memPtr(memPtr),
	bufferSize(bufferSize),
	memoryAlignment(memoryAlignment),
	externalAllocation(true)
{
    if(nullptr != memPtr)
    {
		init();
    }
}

MemoryManager::MemoryManager(int bufferSize, int memoryAlignment):
	MemoryManager(nullptr, bufferSize, memoryAlignment)
{
	memPtr = new unsigned char[this->bufferSize];
	externalAllocation = false;
	if(nullptr != memPtr)
    {
		init();
    }
}

MemoryManager::~MemoryManager()
{
	if(!externalAllocation)
	{
		delete[] memPtr;
	}
}

void MemoryManager::init()
{
    firstBlockInfo = (BlockInfo*) memPtr;
    firstBlockInfo->freeSpace = bufferSize - sizeof(BlockInfo);
    firstBlockInfo->prevBlock = nullptr;
    firstBlockInfo->nextBlock = memPtr + bufferSize;
}

unsigned char *MemoryManager::allocate(unsigned int size)
{
	unsigned char *result = nullptr;
	size = ((size + memoryAlignment - 1) / memoryAlignment) * memoryAlignment;
	for(BlockInfo *ptr = firstBlockInfo; nullptr != ptr; ptr = ptr->nextBlock)
	{
		if(ptr->freeSpace >= size + sizeof(BlockInfo))
		{
            BlockInfo *newBlockInfo = (BlockInfo *)(unsigned char *)(ptr + 1) + size);
            newBlockInfo->nextBlock = ptr->nextBlock;
            newBlockInfo->prevBlock = (unsigned char *)ptr;
            ptr->nextBlock = newBlockInfo;
		}
		if(ptr->freeSpace >= size)
		{
			ptr->freeSpace = 0;
		}
	}

	return result;
}
