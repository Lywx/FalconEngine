#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>

namespace FalconEngine
{

class Lamp : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    Lamp(const NodeSharedPtr node, const Light& light)
        : Entity(node),
          mLight(light)
    {
    }

protected:
    Light mLight;
};

}
