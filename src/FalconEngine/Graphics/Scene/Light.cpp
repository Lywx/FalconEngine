#include <FalconEngine/Graphics/Scene/Light.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Light::Light(LightType lightType) :
    mInnerAngle(0), mOuterAngle(0), mCosAngle(0), mSinAngle(0), mExponent(0),
    mLightType(lightType)
{
}

Light::~Light()
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
LightType Light::GetLightType() const
{
    return mLightType;
}

}
