#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Object);
FALCON_ENGINE_RTTI_IMPLEMENT_EXPORT(Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(PrimitiveSharedPtr primitive) :
    mEffectInstance(),
    mEffectInstancingNum(1),
    mPrimitive(primitive)
{
}

Visual::Visual() :
    mEffectInstance(),
    mEffectInstancingNum(1),
    mPrimitive()
{
}

Visual::~Visual()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const BoundingBox *
Visual::GetBoundingBox() const
{
    return mPrimitive->GetBoundingBox();
}

VisualEffectInstance *
Visual::GetEffectInstance() const
{
    return mEffectInstance.get();
}

void
Visual::SetEffectInstance(VisualEffectInstanceSharedPtr effectInstance)
{
    FALCON_ENGINE_CHECK_NULLPTR(effectInstance);

    mEffectInstance = effectInstance;
}

const Primitive *
Visual::GetPrimitive() const
{
    return mPrimitive.get();
}

void
Visual::SetPrimitive(PrimitiveSharedPtr primitive)
{
    FALCON_ENGINE_CHECK_NULLPTR(primitive);

    mPrimitive = primitive;
}

size_t
Visual::GetEffectInstancingNum() const
{
    return mEffectInstancingNum;
}

void
Visual::SetEffectInstancingNum(size_t effectInstancingNum)
{
    mEffectInstancingNum = effectInstancingNum;
}

void
Visual::UpdateWorldTransform(double elapsed)
{
    Spatial::UpdateWorldTransform(elapsed);
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Visual::CopyTo(Visual *lhs) const
{
    Spatial::CopyTo(lhs);

    lhs->mEffectInstance = mEffectInstance;
    lhs->mEffectInstancingNum = mEffectInstancingNum;
    lhs->mPrimitive = mPrimitive;
}

Visual *
Visual::GetClone() const
{
    auto clone = new Visual();
    CopyTo(clone);
    return clone;
}

}
