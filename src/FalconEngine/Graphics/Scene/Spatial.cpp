#include <FalconEngine/Graphics/Scene/Spatial.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Spatial, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

Spatial::Spatial() :
    mWorldTransformIsCurrent(false),
    mParent(nullptr)
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
    // Update spatial owned data
    UpdateWorldTransform(elaped);

    if (initiator)
    {
    }
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/

void Spatial::UpdateWorldTransform(double elaped)
{
    // Update world transforms.
    if (!mWorldTransformIsCurrent)
    {
        if (mParent)
        {
            mWorldTransform = mParent->mWorldTransform * mLocalTransform;
        }
        else
        {
            mWorldTransform = mLocalTransform;
        }

        mWorldTransformIsCurrent = true;
    }
}

}
