#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/Core/Macro.h>

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

/************************************************************************/
/* Exception Handling                                                   */
/************************************************************************/
#pragma warning(disable: 4275)
class FALCON_ENGINE_ITEM_CORE RuntimeException : public std::runtime_error
{
public:
    explicit RuntimeException(const std::string& message);
};
#pragma warning(default: 4275)

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

}

#define FALCON_ENGINE_CHECK_NULLPTR(pointer) FalconEngine::CheckNullPointer(pointer, #pointer);

#define FALCON_ENGINE_THROW_ASSERTION_EXCEPTION() assert(0);
#define FALCON_ENGINE_THROW_NULLPTR_EXCEPTION(pointer) FalconEngine::ThrowNullException(#pointer);
#define FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(message) throw FalconEngine::RuntimeException(message);
#define FALCON_ENGINE_THROW_SUPPORT_EXCEPTION() throw FalconEngine::RuntimeException("Not implemented.\n");
