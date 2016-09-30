#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

class CullState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    CullState ();
    virtual ~CullState ();

    // Whether enable face culling
    bool CullEnabled = true;

    // Which face to cull
    bool CullCW = true;
};

typedef std::shared_ptr<CullState> CullStatePtr;

}
