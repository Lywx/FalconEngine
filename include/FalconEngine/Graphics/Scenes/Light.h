#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

enum class LightType
{
    Directional,
    Point,
    Spot,

    Count,
};

class Light : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit Light(LightType lightType);
    virtual ~Light();

public:
    /************************************************************************/
    /* General Members                                                      */
    /************************************************************************/
    float    mIntensity = 1;

    Color    mAmbient;
    Color    mDiffuse;
    Color    mSpecular;

    Vector3f mDirection; // Used for directional light or spot light.

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


    LightType
    GetLightType() const
    {
        return mLightType;
    }

private:
    LightType mLightType;
};

}
