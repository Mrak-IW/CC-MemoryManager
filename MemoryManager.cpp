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
	firstBlockInfo->size = bufferSize - sizeof(BlockInfo);
	firstBlockInfo->prev = nullptr;
	firstBlockInfo->next = nullptr;
	firstBlockInfo->isFree = true;
}

unsigned char *MemoryManager::allocate(unsigned int size)
{
	unsigned char *result = nullptr;
	size = ((size + memoryAlignment - 1) / memoryAlignment) * memoryAlignment;
	for(BlockInfo *block = firstBlockInfo; nullptr != block; block = block->next)
	{
		if(block->isFree)
		{
			//If we have to split empty block
			if(block->size >= size + sizeof(BlockInfo))
			{
				//Add a new block info
				BlockInfo *newBlockInfo = (BlockInfo *)((unsigned char *)(block + 1) + size);
				newBlockInfo->next = block->next;
				newBlockInfo->prev = block;
				newBlockInfo->size = block->size - sizeof(BlockInfo) - size;
				newBlockInfo->isFree = true;
				block->next = newBlockInfo;
			}

			if(block->size >= size)
			{
				block->size = size;
				block->isFree = false;
				result = block->getMemPtr();
				break;	//Memory allocated
			}
		}
	}

	return result;
}

void MemoryManager::free(unsigned char *pointer)
{
	BlockInfo *block = (BlockInfo *)pointer - 1;

	/*bool valid = true;
	if(nullptr == block->prev)
	{
		valid &= block == this->firstBlockInfo;
	}*/
	block->isFree = true;

	if(nullptr != block->next && block->next->isFree)
	{
		block->joinNext();
	}

	if(nullptr != block->prev && block->prev->isFree)
	{
		block->prev->joinNext();
	}
}

void MemoryManager::printAllocationData()
{
	for(BlockInfo *block = this->firstBlockInfo; nullptr != block; block = block->next)
	{
        cout<<"BlockAddr:\t"<<block<<endl
			<<"\tisFree:\t"<<block->isFree<<endl
			<<"\tsize:\t"<<block->size<<" + "<<sizeof(BlockInfo)<<endl
			<<"\tprev:\t"<<block->prev<<endl
			<<"\tnext:\t"<<block->next<<endl
			<<endl;
	}
}
