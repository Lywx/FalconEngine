#pragma once

#include <FalconEngine/CoreInclude.h>

#if defined(FALCON_ENGINE_DEBUG_MEMORY)

// Standard memory management.
#define New new
#define NewDebug new(__FILE__, __LINE__)
#define Delete delete
#define DeleteDebug delete(__FILE__, __LINE__)

// Override standard memory management.
#define new New
#define delete Delete

namespace FalconEngine
{

template <typename T>
void DeleteSafe(T *&data)
{
    delete data;
    data = 0;
}

template <typename T>
void DeleteArraySafe(T *&data)
{
    delete[] data;
    data = 0;
}

}

#else
#endif
