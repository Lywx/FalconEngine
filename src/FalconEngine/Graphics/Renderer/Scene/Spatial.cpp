#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

const Rtti Spatial::sType("Spatial", &ObjectsType());
const Rtti& Spatial::GetType() const
{
    return sType;
};

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
Spatial::UpdateWorldTransform(double /* elaped */)
{
    // NOTE(Wuxiang): Update world transforms in an top-to-bottom way. This
    // method is only guaranteed to work when you called it on the root of
    // hierarchy. You should not expect a child node's update would compute world
    // transform correctly if its parent has changed in transformation.
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
