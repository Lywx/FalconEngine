#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class WireframeState sealed
{
public:
    WireframeState();
    ~WireframeState();

public:
    bool mEnabled = false;
};

}
