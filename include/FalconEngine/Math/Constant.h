#pragma once

// NOTE(Wuxiang): Avoid extra header polluting the namespace.
#include <FalconEngine/Math/Type.h>

namespace FalconEngine
{

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
constexpr Real Pi      = Real(3.1415926535897932384626433832795);
constexpr Real PiOver2 = Real(Pi / 2.0);
constexpr Real PiOver4 = Real(Pi / 4.0);
constexpr Real E       = Real(2.71828182846);
constexpr Real Epsilon = Real(1.0e-10);

}
