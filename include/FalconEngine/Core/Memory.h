#pragma once

#include <FalconEngine/CoreInclude.h>

namespace FalconEngine
{

/************************************************************************/
/* Memory Allocation                                                    */
/************************************************************************/
inline int64_t
Kilobytes(int i)
{
    return i * 1024LL;
}

inline int64_t
Megabytes(int i)
{
    return Kilobytes(i) * 1024LL;
}

inline int64_t
Gigabytes(int i)
{
    return Megabytes(i) * 1024LL;
}

inline int64_t
Terabytes(int i)
{
    return Gigabytes(i) * 1024LL;
}

void
PushMemoryRecord(void *pointer, const char *file, size_t line);

void
PopMemoryRecord(void *pointer);

extern const char *__file__;
extern size_t __line__;

}

#if defined(FALCON_ENGINE_DEBUG_MEMORY)
// http://stackoverflow.com/questions/619467/macro-to-replace-c-operator-new
#define New(memoryPool) (FalconEngine::__file__=__FILE__, FalconEngine::__line__=__LINE__) && 0 ? NULL : new(memoryPool)
#define Delete(memoryPointer) (FalconEngine::__file__=__FILE__, FalconEngine::__line__=__LINE__) && 0 ? NULL : delete memoryPointer
#else
#define New(memoryPool) new(memoryPool)
#define Delete(memoryPool) delete(memoryPool)
#endif