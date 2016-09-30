#ifndef BLOCKINFO_H_INCLUDED
#define BLOCKINFO_H_INCLUDED

#include <stdlib.h>

class BlockInfo
{
	public:
		unsigned int size;
		size_t alignment;
		bool isFree;
		BlockInfo *next;
		BlockInfo *prev;

		BlockInfo(unsigned int size, int alignment, bool isFree, BlockInfo *next, BlockInfo *prev);

		unsigned char *getMemPtr();
		void joinNext();

		static size_t getSize(size_t alignment);
	private:
		BlockInfo(){}
};

#endif // BLOCKINFO_H_INCLUDED
