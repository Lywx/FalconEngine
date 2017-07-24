#pragma once

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Math/Vector3.h>
#include "FalconEngine/Math/Color.h"

namespace FalconEngine
{

class Camera;

enum class DebugRenderType
{
    // NOTE(Wuxiang): This list is used to generate mapping. Be careful when you
    // make changes.

    AABB,
    OBB,

    Circle,
    Cross,
    Line,
    Sphere,

    Text,

    Count,
};

class DebugRenderMessage
{
public:
    DebugRenderMessage(const Camera   *camera,
                       DebugRenderType type,
                       float           float1,
                       const Vector3f& floatVector1,
                       const Vector3f& floatVector2,
                       const Color&    color,
                       float           duration,
                       bool            depthEnabled) :
        mCamera(camera),
        mType(type),
        mColor(color),
        mDuration(duration),
        mDepthEnabled(depthEnabled),
        mFloat1(float1),
        mFloatVector1(floatVector1),
        mFloatVector2(floatVector2)
    {
    }

public:
    const Camera   *mCamera;

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
