#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS CullState final
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
