#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(Spatial, ControlledObject);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Spatial::Spatial() :
    WorldTransformIsCurrent(false),
    WorldBoundIsCurrent(false),
    Parent(nullptr)
{
}

Spatial::~Spatial()
{
    // The Parent member is not reference counted by Spatial, so do not
    // release it here. The memory management responsibility belongs to
    // the owner of each Spatial object.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

void Spatial::Update(double elaped, bool initiator)
{
    // Update any controllers associated with this object.
    UpdateControllers(elaped);

    // Update spatial owned data
    UpdateWorldTransform(elaped);
    UpdateWorldBound();

    if (initiator)
    {
        UpdateWorldBoundPropagation();
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/

void Spatial::UpdateWorldTransform(double elaped)
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
