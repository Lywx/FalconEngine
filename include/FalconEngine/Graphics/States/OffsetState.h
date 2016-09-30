#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

/// Managing polygon offset state
class OffsetState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    OffsetState ();
    virtual ~OffsetState ();

    // Set whether offset should be enabled for the various polygon drawing
    // modes (fill, line, point).
    bool OffsetFillEnabled = false;
    bool OffsetLineEnabled = false;
    bool OffsetPointEnabled = false;

    // The offset is factor * dZ + unit * r where dZ is the change in depth
    // relative to the screen space area of the polygon, and r is the smallest
    // resolvable depth difference. Negative values move polygons closer to
    // the eye.
    float OffsetFactor = 0.0f;
    float OffsetUnit = 0.0f;
};

typedef std::shared_ptr<OffsetState> OffsetStatePtr;

}
