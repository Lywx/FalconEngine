#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Entity, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Entity::Entity(NodeSharedPtr node) :
    mNode(node)
{
}

Entity::~Entity()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const NodeSharedPtr
Entity::GetNode() const
{
    return mNode;
}

NodeSharedPtr
Entity::GetNode()
{
    return mNode;
}

void
Entity::Update(GameEngineInput *input, double elapsed)
{
}

}
