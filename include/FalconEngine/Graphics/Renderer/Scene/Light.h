#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{
namespace Detail
{
// 4 x float4.
#pragma pack(push, 4)
struct DirectionalLightData
{
    // Color
    Vector3f mAmbient;
    float _Pad0;

    Vector3f mDiffuse;
    float _Pad1;

    Vector3f mSpecular;
    float _Pad2;

    // Transform
    Vector3f mEyeDirection;
    float _Pad3;
};
#pragma pack(pop)

// 4 x float4.
#pragma pack(push, 4)
struct PointLightData
{
    Vector3f mAmbient;
    float mConstant;

    Vector3f mDiffuse;
    float mLinear;

    Vector3f mSpecular;
    float mQuadratic;

    Vector3f mEyePosition;
    float _Pad0;
};
#pragma pack(pop)

// The layout is not ideal. According to:
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509632(v=vs.85).aspx
//
// 5 x float4.
#pragma pack(push, 4)
struct SpotLightData
{
    Vector3f mAmbient;
    float mConstant;

    Vector3f mDiffuse;
    float mCosAngleInner;

    Vector3f mSpecular;
    float mCosAngleOuter;

    Vector3f mEyeDirection;
    float mLinear;

    Vector3f mEyePosition;
    float mQuadratic;
};
#pragma pack(pop)

}

enum class LightType
{
    Directional,
    Point,
    Spot,

    Count,
};

FALCON_ENGINE_CLASS_BEGIN Light :
public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit Light(LightType lightType);
    virtual ~Light();

public:
    LightType
    GetLightType() const;

public:
    /************************************************************************/
    /* General Members                                                      */
    /************************************************************************/
    Color    mAmbient;
    Color    mDiffuse;
    Color    mSpecular;

    Vector3f mDirection; // Used for directional light or spot light.

    /************************************************************************/
    /* Point Light Members                                                  */
    /************************************************************************/
    float    mConstant;
    float    mLinear;
    float    mQuadratic;

    Vector3f mPosition; // Used for point light or spot light.

    /************************************************************************/
    /* Spot Light Members                                                   */
    /************************************************************************/
    float    mInnerAngle;
    float    mOuterAngle;
    float    mCosAngle;
    float    mSinAngle;
    float    mExponent;

private:
    LightType mLightType;
};
FALCON_ENGINE_CLASS_END

}
