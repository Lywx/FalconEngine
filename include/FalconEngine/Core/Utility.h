#pragma once

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

}
