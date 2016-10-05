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
	size_t alignedMemPtr = (((size_t)memPtr + memoryAlignment - 1) / memoryAlignment) * memoryAlignment;

	firstBlockInfo = (BlockInfo*) alignedMemPtr;

	firstBlockInfo = new (firstBlockInfo) BlockInfo(
		bufferSize - BlockInfo::getSize(memoryAlignment) - (alignedMemPtr - (size_t)memPtr),
		memoryAlignment,
		true,
		nullptr,
		nullptr);
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
			if(block->size >= size + BlockInfo::getSize(memoryAlignment))
			{
				//Add a new block info
				BlockInfo *newBlockInfo = (BlockInfo *)((unsigned char *)block + BlockInfo::getSize(memoryAlignment) + size);

				newBlockInfo = new (newBlockInfo) BlockInfo(
					block->size - BlockInfo::getSize(memoryAlignment) - size,
					memoryAlignment,
					true,
					block->next,
					block);

				block->next = newBlockInfo;
				block->size = size;
			}

			if(block->size >= size)
			{
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
	BlockInfo *block = (BlockInfo *)(pointer - BlockInfo::getSize(memoryAlignment));

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
			<<"\tsize:\t"<<block->size<<" (data) + "<<BlockInfo::getSize(memoryAlignment)<<" (control)"<<endl
			<<"\tprev:\t"<<block->prev<<endl
			<<"\tnext:\t"<<block->next<<endl
			<<endl;
	}
}
