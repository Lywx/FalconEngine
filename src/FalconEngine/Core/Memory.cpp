#include <FalconEngine/CoreInclude.h>

#include <cstdlib>

namespace FalconEngine
{

#if defined(FALCON_ENGINE_DEBUG_MEMORY)
// Declaration lies in Memory.h
const char *__file__ = "Unknown";
size_t      __line__ = 0;

// Declaration lies in Memory.h
void PushMemory(void *pointer, const char *file, size_t line)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

void PopMemory(void *pointer)
{
    // TODO(Wuxiang): Implement to detect memory leak.
}

inline void *operator new(size_t size)
{
    void *pointer = malloc(size);
    PushMemory(pointer, __file__, __line__);

    // Reset to default
    __file__ = "Unknown";
    __line__ = 0;

    return pointer;
}

void operator delete(void *pointer)
{
    PopMemory(pointer);
    free(pointer);
}

#else
#endif

}
