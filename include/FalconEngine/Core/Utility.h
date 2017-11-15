#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>

#include <FalconEngine/Core/Debug.h>

namespace FalconEngine
{

/************************************************************************/
/* Array Handling                                                       */
/************************************************************************/
template<typename T, unsigned N>
constexpr size_t
ArraySize(T(& /* array */)[N])
{
    return N;
}

inline void
ThrowNullException(const std::string& name)
{
    throw RuntimeException(name + " is null.\n");
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

inline void
CheckAssertion(bool value, std::string message)
{
    if (!value)
    {
        throw RuntimeException(message);
    }
}

}

#define FALCON_ENGINE_THROW_ASSERTION_EXCEPTION() throw FalconEngine::RuntimeException("Assertion failed.\n")
#define FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(pointer) FalconEngine::ThrowNullException(#pointer)
#define FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(message) throw FalconEngine::RuntimeException(message)
#define FALCON_ENGINE_THROW_SUPPORT_EXCEPTION() throw FalconEngine::RuntimeException("Not implemented.\n")

#define FALCON_ENGINE_CHECK_ASSERTION(value, message) FalconEngine::CheckAssertion(value, message)
#define FALCON_ENGINE_CHECK_NULLPTR(pointer) FalconEngine::CheckNullPointer(pointer, #pointer)
