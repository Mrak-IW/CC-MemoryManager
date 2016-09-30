#include <iostream>
#include "MemoryManager.h"

using namespace std;

const size_t alignment = 16;

int main()
{
	int sz = BlockInfo::getSize(alignment);
	MemoryManager *mm = new MemoryManager(1024 + BlockInfo::getSize(alignment) * 2, alignment);

	cout<<"**Initial state"<<endl;
	mm->printAllocationData();

	unsigned char *ptr = mm->allocate(10);
	unsigned char *ptr1 = mm->allocate(900);
	unsigned char *ptr2 = mm->allocate(60);
	cout<<"**After allocation"<<endl;
	mm->printAllocationData();

	mm->free(ptr);
	mm->free(ptr1);
	mm->free(ptr2);
	cout<<"**After free"<<endl;
	mm->printAllocationData();

	delete mm;
	return 0;
}
