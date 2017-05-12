#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS WireframeState final
{
public:
    WireframeState();
    ~WireframeState();

public:
    bool mEnabled = false;
};

}
