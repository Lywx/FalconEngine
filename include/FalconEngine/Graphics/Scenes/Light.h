#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

enum class LightType
{
};

class Light : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    Light();
    virtual ~Light();

    Color mAmbient;
    Color mDiffuse;
    Color mSpecular;
};

}
