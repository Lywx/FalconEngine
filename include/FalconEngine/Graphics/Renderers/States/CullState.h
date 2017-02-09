#pragma once

#include <memory>

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

class CullState : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    CullState ();
    virtual ~CullState ();

    // Which face to cull
    bool mCounterClockwise = false;

    // Whether enable face culling
    bool mEnabled = true;
};

typedef std::unique_ptr<CullState> CullStateHandle;

}
