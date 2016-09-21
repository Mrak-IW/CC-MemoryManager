#include <iostream>
#include "MemoryManager.h"

using namespace std;

int main()
{
	MemoryManager *mm = new MemoryManager(1024);
	cout << "Hello world!" << endl;
	return 0;
}
