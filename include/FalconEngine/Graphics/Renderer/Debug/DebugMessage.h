#pragma once

#include <FalconEngine/Graphics/Common.h>

namespace FalconEngine
{

enum class DebugPrimitiveType
{
    None,

    // Bounding box.
    AABB,
    OBB,

    // Geometry primitive.
    Circle,
    Cross,
    Line,
    Sphere,
    Triangle,

    // Others.
    Text,
};

class DebugMessage
{
public:
    bool               mPrimitiveDepthEnabled;
    float              mPrimitiveDuration;
    DebugPrimitiveType mPrimitiveType;
};

}
