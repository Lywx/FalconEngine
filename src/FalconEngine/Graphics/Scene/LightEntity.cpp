#include <FalconEngine/Graphics/Scene/LightEntity.h>

namespace FalconEngine
{

LightEntity::LightEntity(const NodeSharedPtr node) :
    Entity(node),
    mLight(std::make_shared<Light>(LightType::Point))
{
}

LightEntity::LightEntity(const NodeSharedPtr node, const LightSharedPtr light) :
    Entity(node),
    mLight(light)
{
}

}
