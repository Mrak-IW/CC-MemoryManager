#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H


class MemoryManager
{
    public:
        MemoryManager(int bufferSize, int memoryAlignment = 1);
        MemoryManager(unsigned char *memPtr, int bufferSize, int memoryAlignment = 1);
        virtual ~MemoryManager();
    protected:
    private:
        int bufferSize;
        int memoryAlignment;
        unsigned char *memPtr;
};

#endif // MEMORYMANAGER_H
