#pragma once

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Math/Vector3.h>
#include "FalconEngine/Math/Color.h"

namespace FalconEngine
{

enum class DebugRenderType
{
    AABB,
    OBB,

    Circle,
    Cross,
    Line,
    Sphere,

    Text,
};

class DebugRenderMessage
{
public:
    DebugRenderMessage(DebugRenderType type,
                       float           float1,
                       const Vector3f& floatVector1,
                       const Vector3f& floatVector2,
                       const Color&    color,
                       float           duration,
                       bool            depthEnabled) :
        mType(type),
        mColor(color),
        mDuration(duration),
        mDepthEnabled(depthEnabled),
        mFloat1(float1),
        mFloatVector1(floatVector1),
        mFloatVector2(floatVector2)
    {

    }

    // NOTE(Wuxiang): Those are common data field for all different item type.
    DebugRenderType mType;

    Color           mColor;
    float           mDuration;
    bool            mDepthEnabled;

    // NOTE(Wuxiang): Those are different data field which may be zero.
    float           mFloat1;
    Vector3f        mFloatVector1;
    Vector3f        mFloatVector2;
};

}
