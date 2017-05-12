#pragma once

#include <boost/predef.h>

/************************************************************************/
/* Deployment Items                                                     */
/************************************************************************/
// API
#define FALCON_ENGINE_ITEM_CORE_OPENGL 1

// OS
#if BOOST_OS_WINDOWS
#define FALCON_ENGINE_OS_WINDOWS 1
#elif BOOST_OS_LINUX
#define FALCON_ENGINE_OS_LINUX 1
#endif

// DLL
#if FALCON_ENGINE_OS_WINDOWS
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_ITEM_CORE
#if defined(FALCON_ENGINE_BUILD_CORE_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_CORE_EXPORT)
#define FALCON_ENGINE_ITEM_CORE __declspec(dllexport)
#else
#define FALCON_ENGINE_ITEM_CORE __declspec(dllimport)
#endif
#else
#define FALCON_ENGINE_ITEM_CORE
#endif
#endif
#elif FALCON_ENGINE_OS_LINUX
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_BUILD_CORE_DYNAMIC)
#if defined(FALCON_ENGINE_SYMBOL_CORE_EXPORT)
#define FALCON_ENGINE_ITEM_CORE __attribute__ ((visibility("default")))
#endif
#else
#define FALCON_ENGINE_ITEM_CORE
#endif
#endif
#endif

#define FALCON_ENGINE_DEBUG_MEMORY 1

/************************************************************************/
/* Development Items                                                    */
/************************************************************************/
#define _IN_
#define _IN_OUT_
#define _OUT_

