#include <FalconEngine/Graphics/Scene/Character.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Character, Entity);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Character::Character(const NodeSharedPtr node)  :
    Entity(node)
{
}

Character::~Character()
{
}

}
