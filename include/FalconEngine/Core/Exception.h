#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN RuntimeException :
public std::runtime_error
{
public:
    explicit RuntimeException(const std::string & message);
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_CLASS_BEGIN LogicError :
public std::logic_error
{
public:
    explicit LogicError(const std::string & message);
};
FALCON_ENGINE_CLASS_END

namespace
{

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

}

#define FALCON_ENGINE_CHECK_ASSERTION(value, message) FalconEngine::CheckAssertion(value, message)
#define FALCON_ENGINE_CHECK_NULLPTR(pointer) FalconEngine::CheckNullPointer(pointer, #pointer)

#define FALCON_ENGINE_THROW_ASSERTION_EXCEPTION() throw FalconEngine::RuntimeException("Assertion failed.\n")
#define FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(pointer) FalconEngine::ThrowNullException(#pointer)
#define FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(message) throw FalconEngine::RuntimeException(message)
#define FALCON_ENGINE_THROW_SUPPORT_EXCEPTION() throw FalconEngine::RuntimeException("Not implemented.\n")
