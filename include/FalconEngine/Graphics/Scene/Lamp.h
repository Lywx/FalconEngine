#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Scene/Light.h>

namespace FalconEngine
{

class Lamp : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    Lamp();

protected:
    Light mLight;
};

}
