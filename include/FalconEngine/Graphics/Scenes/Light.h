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
    Color mAmbient;
    Color mDiffuse;
    Color mSpecular;

    Vector3f mPosition;

    LightType
    GetLightType() const
    {
        return mLightType;
    }

private:
    LightType mLightType;
};

}
