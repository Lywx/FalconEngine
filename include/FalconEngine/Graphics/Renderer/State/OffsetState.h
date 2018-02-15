#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

// @summary Polygon offset state
// @note offset = factor * m + unit * r. m is the change in depth
// relative to the screen space area of the polygon, and r is the smallest
// resolvable depth difference (OpenGL implementation specific). Negative
// values move polygons closer to the eye.
// @ref Dave Shreiner, etc OpenGL Programming Guide, 8th, 2013, P164
FALCON_ENGINE_CLASS_BEGIN OffsetState final
{
public:
    OffsetState();
    ~OffsetState() = default;

public:
    bool  mFillEnabled  = false;
    bool  mLineEnabled  = false;
    bool  mPointEnabled = false;

    float mFactor = 0.0f; // Offset factor, positive or negative
    float mUnit   = 0.0f; // Offset unit, positive or negative
};
FALCON_ENGINE_CLASS_END

}
