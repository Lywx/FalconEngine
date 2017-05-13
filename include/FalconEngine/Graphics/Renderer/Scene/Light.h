#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API LightType
{
    Directional,
    Point,
    Spot,

    Count,
};

class Light;
using LightSharedPtr = std::shared_ptr<Light>;

class FALCON_ENGINE_API Light : public Object
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
    Color    mAmbient = ColorPalette::Transparent;
    Color    mDiffuse = ColorPalette::Transparent;
    Color    mSpecular = ColorPalette::Transparent;

    // NOTE(Wuxiang): Used for directional light or spot light.
    Vector3f mDirection = Vector3f::Zero;

    /************************************************************************/
    /* Point Light Members                                                  */
    /************************************************************************/
    float    mConstant = 1;
    float    mLinear = 0;
    float    mQuadratic = 0;

    Vector3f mPosition = Vector3f::Zero; // Used for point light or spot light.

    /************************************************************************/
    /* Spot Light Members                                                   */
    /************************************************************************/
    float    mInnerAngle;
    float    mOuterAngle;     // default: pi
    float    mCosAngle;  // default: -1
    float    mSinAngle;  // default:  0
    float    mExponent;  // default:  1

private:
    LightType mLightType;
};

}
