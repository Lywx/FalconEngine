#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

class WireframeState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    WireframeState ();
    virtual ~WireframeState ();

    bool Enabled = false;
};

typedef std::shared_ptr<WireframeState> WireframeStatePtr;

}
