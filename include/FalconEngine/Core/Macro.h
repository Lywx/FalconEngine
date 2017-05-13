#pragma once

#include <boost/predef.h>

/************************************************************************/
/* Deployment Items                                                     */
/************************************************************************/
// API
#define FALCON_ENGINE_API_OPENGL

// OS
#if BOOST_OS_WINDOWS
#define FALCON_ENGINE_OS_WINDOWS
#elif BOOST_OS_LINUX
#define FALCON_ENGINE_OS_LINUX
#endif

// DLL
#if defined(FALCON_ENGINE_OS_WINDOWS)
#if defined(FALCON_ENGINE_COMPILER_MSVC)
#undef FALCON_ENGINE_API
#if defined(FALCON_ENGINE_SYMBOL_EXPORT)
#define FALCON_ENGINE_API __declspec(dllexport)
#elif defined(FALCON_ENGINE_SYMBOL_IMPORT)
#define FALCON_ENGINE_API __declspec(dllimport)
#else
#define FALCON_ENGINE_API
#endif
#endif
#elif defined(FALCON_ENGINE_OS_LINUX)
#if defined(FALCON_ENGINE_COMPILER_GCC)
#if defined(FALCON_ENGINE_SYMBOL_EXPORT)
#define FALCON_ENGINE_API __attribute__ ((visibility("default")))
#else
#define FALCON_ENGINE_API
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

