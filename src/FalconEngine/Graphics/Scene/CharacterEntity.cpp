#include <FalconEngine/Graphics/Scene/CharacterEntity.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(CharacterEntity, Entity);
FALCON_ENGINE_RTTI_IMPLEMENT_EXPORT(CharacterEntity);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
CharacterEntity::CharacterEntity(const NodeSharedPtr node)  :
    Entity(node)
{
}

CharacterEntity::~CharacterEntity()
{
}

}
