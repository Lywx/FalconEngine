#pragma once

#include <FalconEngine/Core/CoreInclude.h>

/************************************************************************/
/* Memory Allocation                                                    */
/************************************************************************/
inline int64_t Kilobytes(int i);
inline int64_t Megabytes(int i);
inline int64_t Gigabytes(int i);
inline int64_t Terabytes(int i);

#if defined(FALCON_ENGINE_DEBUG_MEMORY)
// http://stackoverflow.com/questions/619467/macro-to-replace-c-operator-new
// Definition lies in Memory.cpp
extern const char *__file__;
extern size_t __line__;
#define New(MemoryPool) (__file__=__FILE__,__line__=__LINE__) && 0 ? NULL : new(MemoryPool)

// Definition lies in Memory.cpp
void PushMemoryRecord(void *pointer, const char *file, size_t line);
void PopMemoryRecord(void *pointer);
#else
#define New new
#endif