#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
#include <new>
#include "BlockInfo.h"

using namespace std;

class MemoryManager
{
	public:
		MemoryManager(int bufferSize, int memoryAlignment = 1);
		MemoryManager(unsigned char *memPtr, int bufferSize, int memoryAlignment = 1);
		virtual ~MemoryManager();

		unsigned char *allocate(unsigned int size);
		void free(unsigned char *pointer);

		void printAllocationData();
	protected:
		void init();
	private:
		int bufferSize;
		int memoryAlignment;
		unsigned char *memPtr;
		BlockInfo *firstBlockInfo;
		bool externalAllocation;
};

#endif // MEMORYMANAGER_H
