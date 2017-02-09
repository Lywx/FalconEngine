#pragma once

#include <memory>

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

class WireframeState : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    WireframeState ();
    virtual ~WireframeState ();

    bool mEnabled = false;
};

typedef std::unique_ptr<WireframeState> WireframeStateHandle;

}
