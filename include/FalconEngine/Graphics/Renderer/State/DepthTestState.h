#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

enum class DepthFunction
{
    NEVER,         // Never passes.
    LESS,          // Passes if the incoming depth value is less than the stored depth value.
    EQUAL,         // Passes if the incoming depth value is equal to the stored depth value.
    LESS_EQUAL,    // Passes if the incoming depth value is less than or equal to the stored depth value.
    GREATER,       // Passes if the incoming depth value is greater than the stored depth value.
    NOT_EQUAL,     // Passes if the incoming depth value is not equal to the stored depth value.
    GREATER_EQUAL, // Passes if the incoming depth value is greater than or equal to the stored depth value.
    ALWAYS,        // Always passes.

    Count
};

inline int
DepthFunctionIndex(DepthFunction depthFunction)
{
    return int(depthFunction);
}

FALCON_ENGINE_CLASS_BEGIN DepthTestState final
{
public:
    DepthTestState();
    ~DepthTestState();

public:
    // Enable depth testing
    bool mEnabled = true;

    // Enable depth value writing in frame buffer
    bool mWriteEnabled = true;
    DepthFunction mCompareFunction = DepthFunction::LESS_EQUAL;
};
FALCON_ENGINE_CLASS_END

}
