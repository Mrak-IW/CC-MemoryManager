#ifndef BLOCKINFO_H_INCLUDED
#define BLOCKINFO_H_INCLUDED

struct BlockInfo
{
	unsigned int freeSpace;
	unsigned char *nextBlock;
	unsigned char *prevBlock;
	unsigned char *getMemPtr() { return (unsigned char *)(this + 1); }
};

#endif // BLOCKINFO_H_INCLUDED
