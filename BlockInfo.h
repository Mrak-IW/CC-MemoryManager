#ifndef BLOCKINFO_H_INCLUDED
#define BLOCKINFO_H_INCLUDED

struct BlockInfo
{
	unsigned int size;
	bool isFree;
	BlockInfo *next;
	BlockInfo *prev;

	unsigned char *getMemPtr();
	void joinNext();
};

#endif // BLOCKINFO_H_INCLUDED
