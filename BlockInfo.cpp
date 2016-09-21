#include "BlockInfo.h"

unsigned char *BlockInfo::getMemPtr()
{
	return (unsigned char *)(this + 1);
}

void BlockInfo::joinNext()
{
	if(nullptr != this->next)
	{
		this->size += this->next->size + sizeof(BlockInfo);
		this->next = this->next->next;
		if(nullptr != this->next)
		{
			this->next->prev = this;
		}
	}
}
