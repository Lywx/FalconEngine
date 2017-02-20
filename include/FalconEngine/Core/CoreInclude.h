#pragma once

#include <climits>
#include <cstdint>
#include <stdexcept>
#include <string>

#include <boost/predef.h>
#include <memory>

/************************************************************************/
/* Deployment Items                                                     */
/************************************************************************/
#if BOOST_OS_WINDOWS
#define FALCON_ENGINE_OS_WINDOWS 1
#elif BOOST_OS_LINUX
#define FALCON_ENGINE_OS_LINUX 1
#endif
#define FALCON_ENGINE_API_OPENGL 1
#define FALCON_ENGINE_DEBUG_MEMORY 1

/************************************************************************/
/* Helper Items                                                         */
/************************************************************************/
#define FALCON_ENGINE_NOT_SUPPORT() assert(0);
#define FALCON_ENGINE_NOT_POSSIBLE() assert(0);

namespace FalconEngine
{

inline void
ThrowRuntimeException(const std::string& error)
{
    throw std::runtime_error(error);
}

inline void
ThrowNullException(const std::string& name)
{
    throw std::invalid_argument(name + " is null.");
}

inline void
CheckNullPointer(const void *pointer, const std::string name)
{
    if (!pointer)
    {
        ThrowNullException(name);
    }
}

template<typename T>
inline void
CheckNullPointer(const std::shared_ptr<T> pointer, const std::string name)
{
    if (!pointer)
    {
        ThrowNullException(name);
    }
}

}

#define FALCON_ENGINE_CHECK_NULLPTR(pointer) FalconEngine::CheckNullPointer(pointer, #pointer);

#define IN
#define OUT
