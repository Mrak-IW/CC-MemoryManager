#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned char *memPtr, int bufferSize, int memoryAlignment)
	: memPtr(memPtr), bufferSize(bufferSize), memoryAlignment(memoryAlignment)
{ }

MemoryManager::MemoryManager(int bufferSize, int memoryAlignment)
	: MemoryManager(nullptr, bufferSize, memoryAlignment)
{
	memPtr = new unsigned char[bufferSize];
}

MemoryManager::~MemoryManager()
{
    //dtor
}
