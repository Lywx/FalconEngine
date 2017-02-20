#include <FalconEngine/Core/MemoryPool.h>

namespace FalconEngine
{

MemoryPool::MemoryPool(int64_t byte) :
    mStorageSize(byte),
    mStorage(malloc(byte))
{
}

MemoryPool::~MemoryPool()
{
    free(mStorage);
}

}
