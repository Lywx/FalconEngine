#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

enum class DepthFunction
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

class DepthTestState sealed
{
public:
    DepthTestState();
    ~DepthTestState();

public:
    bool          mTestEnabled     = true; // Enable depth testing
    bool          mWriteEnabled    = true; // Enable depth value writing in frame buffer
    DepthFunction mCompareFunction = DepthFunction::LEQUAL;
};

}