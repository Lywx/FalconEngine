#pragma once

#include <FalconEngine/CoreInclude.h>

namespace FalconEngine
{

#if defined(FALCON_ENGINE_DEBUG_MEMORY)

// http://stackoverflow.com/questions/619467/macro-to-replace-c-operator-new
// Definition lies in Memory.cpp
extern const char *__file__;
extern size_t __line__;
#define new (__file__=__FILE__,__line__=__LINE__) && 0 ? NULL : new
#define delete (__file__=__FILE__,__line__=__LINE__) && 0 ? NULL : delete
#else
#endif

// Definition lies in Memory.cpp
void PushMemory(void *pointer, const char *file, size_t line);
void PopMemory(void *pointer);

}
