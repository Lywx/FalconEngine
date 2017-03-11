#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Spatial, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Spatial::Spatial() :
    mLocalTransform(Matrix4f::Identity),
    mWorldTransform(Matrix4f::Identity),
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
void
Spatial::Update(double elaped, bool initiator)
{
    // Update spatial owned data
    UpdateWorldTransform(elaped);

    if (initiator)
    {
    }
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Spatial::CopyTo(Spatial *lhs) const
{
    lhs->mWorldTransform = mWorldTransform;
    lhs->mLocalTransform = mLocalTransform;
    lhs->mWorldTransformIsCurrent = mWorldTransformIsCurrent;

    // NOTE(Wuxiang): The copying won't try to copy the ownership and parentage.
    lhs->mParent = nullptr;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Spatial::UpdateWorldTransform(double elaped)
{
    // Update world transforms.
    if (!mWorldTransformIsCurrent)
    {
        if (mParent)
        {
            //if (mParent->mWorldTransformIsCurrent)
            //{
            mWorldTransform = mParent->mWorldTransform * mLocalTransform;
            //}
            //else
            //{
            //    // NOTE(Wuxiang): Let parent update transform first. The parent
            //    // update call would call this method again. By the time, this
            //    // method is called again, the mWorldTransformIsCurrent field in
            //    // parent would evaluated to be true.
            //    mParent->UpdateWorldTransform(elaped);
            //}
        }
        else
        {
            mWorldTransform = mLocalTransform;
        }

        mWorldTransformIsCurrent = true;
    }
}

}
