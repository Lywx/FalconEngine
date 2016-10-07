#pragma once

#ifdef FALCON_ENGINE_USE_MEMORY

#else

// Standard memory management.
#define New new
#define NewDebug new(__FILE__, __LINE__)
#define Delete delete
#define DeleteDebug delete(__FILE__, __LINE__)

// Override standard memory management.
#define new New
#define delete Delete

namespace FalconEngine {

template <typename T>
void DeleteSafe(T *&data)
{
    Delete data;
    data = 0;
}

template <typename T>
void DeleteArraySafe(T *&data)
{
    Delete[] data;
    data = 0;
}

}

#endif
