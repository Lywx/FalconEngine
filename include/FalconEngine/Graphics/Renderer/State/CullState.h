#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class CullState final
{
public:
    CullState ();
    ~CullState ();

public:
    // Which face to cull
    bool mCounterClockwise = false;

    // Whether enable face culling
    bool mEnabled = true;
};

}
