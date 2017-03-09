#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

enum class LightType
{
    Directional,
    Point,
    Spot,

    Count,
};

class Light;
using LightSharedPtr = std::shared_ptr<Light>;

class Light : public Object
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
    float    mIntensity = 1;

    Color    mAmbient = ColorPalette::White;
    Color    mDiffuse = ColorPalette::White;
    Color    mSpecular = ColorPalette::White;

    // NOTE(Wuxiang): Used for directional light or spot light.
    Vector3f mDirection = Vector3f::Zero;

    /************************************************************************/
    /* Point Light Members                                                  */
    /************************************************************************/
    float    mConstant = 1;
    float    mLinear = 0;
    float    mQuadratic = 0;

    Vector3f mPosition; // Used for point light or spot light.

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
