#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>

namespace FalconEngine
{

class LightEntity;
using LightEntitySharedPtr = std::shared_ptr<LightEntity>;

class LightEntity : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit LightEntity(const NodeSharedPtr node);
    LightEntity(const NodeSharedPtr node, const LightSharedPtr light);

public:
    LightSharedPtr mLight;
};

}
