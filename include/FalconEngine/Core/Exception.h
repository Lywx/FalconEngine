#pragma once

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

}
