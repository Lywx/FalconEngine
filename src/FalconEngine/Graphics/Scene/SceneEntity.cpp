#include <FalconEngine/Graphics/Scene/SceneEntity.h>

#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
SceneEntity::SceneEntity() :
    SceneEntity(std::make_shared<Node>())
{
}

SceneEntity::SceneEntity(const std::shared_ptr<Node>& node) :
    Entity(node)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void SceneEntity::Update(GameEngineInput * /* input */, double elapsed)
{
    mNode->Update(elapsed, true);
}

}
