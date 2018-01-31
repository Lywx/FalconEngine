#pragma once

#include <FalconEngine/Core/Macro.h>

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
