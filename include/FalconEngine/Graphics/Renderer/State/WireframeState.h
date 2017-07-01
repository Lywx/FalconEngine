#pragma once

#include <FalconEngine/Graphics/Common.h>

namespace FalconEngine
{

class FALCON_ENGINE_API WireframeState final
{
public:
    WireframeState();
    ~WireframeState();

public:
    bool mEnabled = false;
};

}
