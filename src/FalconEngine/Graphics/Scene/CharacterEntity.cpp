#include <FalconEngine/Graphics/Scene/CharacterEntity.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(CharacterEntity, Entity);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
CharacterEntity::CharacterEntity(const NodeSharedPtr node)  :
    SceneEntity(node)
{
}

CharacterEntity::~CharacterEntity()
{
}

}
