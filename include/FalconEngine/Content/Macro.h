#pragma once

#include <FalconEngine/Core/Macro.h>

// DLL
#if defined(FALCON_ENGINE_OS_WINDOWS)
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_ITEM_CONTENT
#if defined(FALCON_ENGINE_SYMBOL_CONTENT_EXPORT)
#define FALCON_ENGINE_ITEM_CONTENT __declspec(dllexport)
#elif defined(FALCON_ENGINE_SYMBOL_CONTENT_IMPORT)
#define FALCON_ENGINE_ITEM_CONTENT __declspec(dllimport)
#else
#define FALCON_ENGINE_ITEM_CONTENT
#endif
#endif
#elif defined(FALCON_ENGINE_OS_LINUX)
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_SYMBOL_CONTENT_EXPORT)
#define FALCON_ENGINE_ITEM_CONTENT __attribute__ ((visibility("default")))
#else
#define FALCON_ENGINE_ITEM_CONTENT
#endif
#endif
#endif

