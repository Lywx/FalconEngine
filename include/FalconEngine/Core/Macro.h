#pragma once

#include <boost/predef.h>

/************************************************************************/
/* Deployment Items                                                     */
/************************************************************************/
// API
#define FALCON_ENGINE_API_OPENGL

// OS
#if defined(BOOST_OS_WINDOWS)
#define FALCON_ENGINE_OS_WINDOWS
#elif defined(BOOST_OS_LINUX)
#define FALCON_ENGINE_OS_LINUX
#endif

// DLL
#if defined(FALCON_ENGINE_OS_WINDOWS)
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_ITEM_CORE
#if defined(FALCON_ENGINE_SYMBOL_CORE_EXPORT)
#define FALCON_ENGINE_ITEM_CORE __declspec(dllexport)
#elif defined(FALCON_ENGINE_SYMBOL_CORE_IMPORT)
#define FALCON_ENGINE_ITEM_CORE __declspec(dllimport)
#else
#define FALCON_ENGINE_ITEM_CORE
#endif
#endif
#elif defined(FALCON_ENGINE_OS_LINUX)
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_SYMBOL_CORE_EXPORT)
#define FALCON_ENGINE_ITEM_CORE __attribute__ ((visibility("default")))
#else
#define FALCON_ENGINE_ITEM_CORE
#endif
#endif
#endif

#define FALCON_ENGINE_DEBUG_MEMORY

/************************************************************************/
/* Development Items                                                    */
/************************************************************************/
#define _IN_
#define _IN_OUT_
#define _OUT_

