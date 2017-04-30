#pragma once

#include <climits>
#include <cstdint>
#include <stdexcept>
#include <string>

#include <boost/predef.h>
#include <memory>

#include <FalconEngine/Core/Debug.h>

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
/* Development Items                                                    */
/************************************************************************/
#define _IN_
#define _IN_OUT_
#define _OUT_

/************************************************************************/
/* Helper Items                                                         */
/************************************************************************/
namespace FalconEngine
{

// Array Handlinig
template<typename T, unsigned N>
size_t
ArraySize(T(& /* array */)[N])
{
    return N;
}

// Exception Handlinig
class RuntimeException : public std::runtime_error
{
public:
    RuntimeException(const std::string& message) :
        runtime_error(message)
    {
        Debug::OutputString(message);
    }
};

inline void
ThrowNullException(const std::string& name)
{
    throw std::invalid_argument(name + " is null.\n");
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
#define FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(pointer) FalconEngine::ThrowNullException(#pointer);

#define FALCON_ENGINE_THROW_ASSERTION_EXCEPTION() assert(0);
#define FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(message) throw FalconEngine::RuntimeException(message);
#define FALCON_ENGINE_THROW_SUPPORT_EXCEPTION() throw FalconEngine::RuntimeException("No support for this yet.\n");
