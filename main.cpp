#include <iostream>
#include "MemoryManager.h"

using namespace std;

int main()
{
	int sz = sizeof(BlockInfo);
	MemoryManager *mm = new MemoryManager(1024 + sizeof(BlockInfo));
	cout<<"**Initial state"<<endl;
	mm->printAllocationData();
	cout<<"**After allocation"<<endl;
	unsigned char *ptr = mm->allocate(10);
	mm->printAllocationData();
	cout<<"**After free"<<endl;
	mm->free(ptr);
	mm->printAllocationData();

	delete mm;
	return 0;
}
