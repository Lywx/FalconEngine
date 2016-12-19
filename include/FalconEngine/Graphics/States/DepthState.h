#pragma once

#include <memory>

#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

enum class DepthCompareFunction
{
    NEVER,    // Never passes.
    LESS,     // Passes if the incoming depth value is less than the stored depth value.
    EQUAL,    // Passes if the incoming depth value is equal to the stored depth value.
    LEQUAL,   // Passes if the incoming depth value is less than or equal to the stored depth value.
    GREATER,  // Passes if the incoming depth value is greater than the stored depth value.
    NOTEQUAL, // Passes if the incoming depth value is not equal to the stored depth value.
    GEQUAL,   // Passes if the incoming depth value is greater than or equal to the stored depth value.
    ALWAYS,

    Count
};

class DepthState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    DepthState ();
    virtual ~DepthState ();

    bool DepthTestEnabled = true;
    bool DepthWriteEnabled = true;
    DepthCompareFunction DepthCompareFunction = DepthCompareFunction::LEQUAL;
};

typedef std::shared_ptr<DepthState> DepthStatePtr;

}
