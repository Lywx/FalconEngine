#pragma once

#include <cstdint>

#include <FalconEngine/Core/Macro.h>

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
#define FALCON_ENGINE_NEW(memoryPool) (FalconEngine::__file__=__FILE__, FalconEngine::__line__=__LINE__) && 0 ? NULL : new(memoryPool)
#define FALCON_ENGINE_DELETE(memoryPointer) (FalconEngine::__file__=__FILE__, FalconEngine::__line__=__LINE__) && 0 ? NULL : delete memoryPointer
#else
#define FALCON_ENGINE_NEW(memoryPool) new(memoryPool)
#define FALCON_ENGINE_DELETE(memoryPool) delete(memoryPool)
#endif

#define FALCON_ENGINE_DELETER_DECLARE(PlatformClass, PlatformDeleterClass) \
class PlatformDeleterClass \
{ \
public: \
    void operator()(PlatformClass *platformClass); \
}; \

#define FALCON_ENGINE_DELETER_IMPLEMENT(PlatformClass, PlatformDeleterClass) \
void \
PlatformDeleterClass::operator()(PlatformClass *platformClass) \
{ \
    delete platformClass; \
}

// NOTE(Wuxiang): On concern about static method copy in different translation unit, read:
// http://stackoverflow.com/questions/5372091/are-static-member-functions-in-c-copied-in-multiple-translation-units
// http://stackoverflow.com/questions/12248747/singleton-with-multithreads
#define FALCON_ENGINE_SINGLETON_LEAK_DECLARE(SingletonClass) \
public: \
    static SingletonClass * \
    GetInstance() \
    { \
        static SingletonClass sInstance; \
        return &sInstance; \
    } \

#define FALCON_ENGINE_SINGLETON_SAFE_DECLARE(SingletonClass) \
FALCON_ENGINE_SINGLETON_LEAK_DECLARE(SingletonClass) \
public: \
    void \
    Destroy();

