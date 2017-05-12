#pragma once

#include <FalconEngine/Core/Macro.h>

// DLL
#if FALCON_ENGINE_OS_WINDOWS
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_ITEM_MATH
#if defined(FALCON_ENGINE_BUILD_MATH_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_MATH_EXPORT)
#define FALCON_ENGINE_ITEM_MATH __declspec(dllexport)
#else
#define FALCON_ENGINE_ITEM_MATH __declspec(dllimport)
#endif
#else
#define FALCON_ENGINE_ITEM_MATH
#endif
#endif
#elif FALCON_ENGINE_OS_LINUX
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_BUILD_MATH_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_MATH_EXPORT)
#define FALCON_ENGINE_ITEM_MATH __attribute__ ((visibility("default")))
#endif
#else
#define FALCON_ENGINE_ITEM_MATH
#endif
#endif
#endif

