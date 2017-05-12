#pragma once

#include <FalconEngine/Core/Macro.h>

// DLL
#if FALCON_ENGINE_OS_WINDOWS
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_ITEM_INPUT
#if defined(FALCON_ENGINE_BUILD_INPUT_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_INPUT_EXPORT)
#define FALCON_ENGINE_ITEM_INPUT __declspec(dllexport)
#else
#define FALCON_ENGINE_ITEM_INPUT __declspec(dllimport)
#endif
#else
#define FALCON_ENGINE_ITEM_INPUT
#endif
#endif
#elif FALCON_ENGINE_OS_LINUX
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_BUILD_INPUT_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_INPUT_EXPORT)
#define FALCON_ENGINE_ITEM_INPUT __attribute__ ((visibility("default")))
#endif
#else
#define FALCON_ENGINE_ITEM_INPUT
#endif
#endif
#endif

