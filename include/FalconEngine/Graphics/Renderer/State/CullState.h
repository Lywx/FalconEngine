#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN CullState final
{
public:
    CullState();
    ~CullState();

public:
    // Which face to cull
    bool mCounterClockwise = false;

    // Whether enable face culling
    bool mEnabled = true;
};
FALCON_ENGINE_CLASS_END

}
