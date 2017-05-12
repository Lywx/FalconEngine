#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Core/MemoryPool.h>

#include <cstdlib>

namespace FalconEngine
{

const char *__file__ = "Unknown";
size_t      __line__ = 0;

void
PushMemoryRecord(void * /* pointer */, const char * /* file */, size_t /* line */)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

void
PopMemoryRecord(void * /* pointer */)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

}

using namespace FalconEngine;

void *
operator new(size_t size, MemoryPool *memory)
{
    using namespace FalconEngine;

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

void *
operator new[](size_t size, MemoryPool *memory)
{
    using namespace FalconEngine;

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

void
operator delete[](void *pointer, MemoryPool * /* memory */)
{
    using namespace FalconEngine;

    PopMemoryRecord(pointer);
    free(pointer);
}

void
operator delete(void *pointer, MemoryPool * /* memory */)
{
    using namespace FalconEngine;

    PopMemoryRecord(pointer);
    free(pointer);
}
