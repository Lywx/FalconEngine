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

}
