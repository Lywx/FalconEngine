#include <FalconEngine/Graphics/Renderer/Scene/Light.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Light, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Light::Light(LightType lightType) :
    mAmbient(ColorPalette::Transparent),
    mDiffuse(ColorPalette::Transparent),
    mSpecular(ColorPalette::Transparent),
    mDirection(Vector3f::Zero),
    mConstant(1),
    mLinear(0),
    mQuadratic(0),
    mPosition(Vector3f::Zero),
    mInnerAngle(0),
    mOuterAngle(0),
    mCosAngle(0),
    mSinAngle(0),
    mExponent(0),
    mLightType(lightType)
{
}

Light::~Light()
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
LightType
Light::GetLightType() const
{
    return mLightType;
}

}
