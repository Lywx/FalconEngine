#pragma once

#include <FalconEngine/Core/Common.h>

namespace FalconEngine
{

class MemoryPool;

}

void *operator new(size_t size, FalconEngine::MemoryPool *memory);
void *operator new[](size_t size, FalconEngine::MemoryPool *memory);

namespace FalconEngine
{

// NOTE(Wuxiang): Learned form handmade hero. To use this, you need to allocate
// memory storage first.
class FALCON_ENGINE_API MemoryPool final
{
public:
    MemoryPool(int64_t byte);
    ~MemoryPool();

protected:
    int64_t mStorageSize;
    void   *mStorage;

private:
    friend void *::operator new(size_t size, MemoryPool *memory);
    friend void *::operator new[](size_t size, MemoryPool *memory);
};

}
