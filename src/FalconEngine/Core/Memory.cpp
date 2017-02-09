#include <FalconEngine/Core/CoreInclude.h>
#include <FalconEngine/Core/MemoryPool.h>

#include <cstdlib>

using namespace FalconEngine;

inline int64_t Kilobytes(int i)
{
    return i * 1024LL;
}

inline int64_t Megabytes(int i)
{
    return Kilobytes(i) * 1024LL;
}

inline int64_t Gigabytes(int i)
{
    return Megabytes(i) * 1024LL;
}

inline int64_t Terabytes(int i)
{
    return Gigabytes(i) * 1024LL;
}

#if defined(FALCON_ENGINE_DEBUG_MEMORY)
// Declaration lies in Memory.h
const char *__file__ = "Unknown";
size_t      __line__ = 0;

// Declaration lies in Memory.h
void PushMemoryRecord(void *pointer, const char *file, size_t line)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

void PopMemoryRecord(void *pointer)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

inline void *operator new(size_t size, MemoryPool *memory)
{
    void *pointer = memory->mStorage;

    // Modify storage
    memory->mStorage = reinterpret_cast<uint8_t *>(pointer) + size;
    memory->mStorageSize += size;

    PushMemoryRecord(pointer, __file__, __line__);

    // Reset to default
    __file__ = "Unknown";
    __line__ = 0;

    return pointer;
}

inline void *operator new[](size_t size, MemoryPool *memory)
{
    void *pointer = memory->mStorage;

    // Modify storage
    memory->mStorage = reinterpret_cast<uint8_t *>(pointer) + size;
    memory->mStorageSize += memory->mStorageSize + size;

    PushMemoryRecord(pointer, __file__, __line__);

    // Reset to default
    __file__ = "Unknown";
    __line__ = 0;

    return pointer;
}

void operator delete[](void *pointer, MemoryPool *memory)
{
    PopMemoryRecord(pointer);
    free(pointer);
}

void operator delete(void *pointer, MemoryPool *memory)
{
    PopMemoryRecord(pointer);
    free(pointer);
}

#else
#endif
