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

    Aabb,
    Obb,

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
    DebugRenderMessage(DebugRenderType type,
                       const Color&    color,
                       float           duration,
                       bool            depthEnabled) :
        mType(type),
        mCamera(),
        mColor(color),
        mDuration(duration),
        mDepthEnabled(depthEnabled),
        mFloat1(),
        mFloat2(),
        mFloatVector1(),
        mFloatVector2(),
        mString1()
    {
    }

public:
    // NOTE(Wuxiang): Those are common data field for all different item type.
    DebugRenderType mType;

    const Camera   *mCamera;
    Color           mColor;
    float           mDuration;
    bool            mDepthEnabled;

    // NOTE(Wuxiang): Those are different data field which may be zero.
    float           mFloat1;
    float           mFloat2;
    Vector3f        mFloatVector1;
    Vector3f        mFloatVector2;

    std::string     mString1;
};

}
