#include "BlockInfo.h"

BlockInfo::BlockInfo(unsigned int size, int alignment, bool isFree, BlockInfo *next, BlockInfo *prev):
	size(size),
	alignment(alignment),
	isFree(isFree),
	next(next),
	prev(prev)
{ }

unsigned char *BlockInfo::getMemPtr()
{
	return (unsigned char *)this + getSize(alignment);
}

void BlockInfo::joinNext()
{
	if(nullptr != this->next)
	{
		this->size += this->next->size + getSize(alignment);
		this->next = this->next->next;
		if(nullptr != this->next)
		{
			this->next->prev = this;
		}
	}
}

size_t BlockInfo::getSize(size_t alignment)
{
	return ((sizeof(BlockInfo) + alignment - 1) / alignment) * alignment;
}
