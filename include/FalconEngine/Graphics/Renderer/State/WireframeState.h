#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class WireframeState final
{
public:
    WireframeState();
    ~WireframeState();

public:
    bool mEnabled = false;
};

}
