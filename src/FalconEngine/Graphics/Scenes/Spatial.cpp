#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(Spatial, ControlledObject);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Spatial::Spatial()
{
}

Spatial::~Spatial()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Spatial::Update(double elaped)
{
    // Update any controllers associated with this object.
    UpdateControllers(elaped);

    UpdateWorldData(elaped);
    UpdateWorldBound();

    if (initiator)
    {
        UpdateWorldBoundPropagation();
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void Spatial::UpdateWorldData(double elaped)
{
    // Update world transforms.
    if (!WorldTransformIsCurrent)
    {
        if (Parent)
        {
            WorldTransform = Parent->WorldTransform * LocalTransform;
        }
        else
        {
            WorldTransform = LocalTransform;
        }
    }
}

void Spatial::UpdateWorldBoundPropagation()
{
    if (Parent)
    {
        Parent->UpdateWorldBound();
        Parent->UpdateWorldBoundPropagation();
    }
}

}

