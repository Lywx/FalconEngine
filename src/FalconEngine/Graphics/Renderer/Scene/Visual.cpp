#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(PrimitiveSharedPtr primitive) :
    mPrimitive(primitive),
    mPrimitiveInstancingNum(1)
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
Visual::GetPrimitiveInstancingNum() const
{
    return mPrimitiveInstancingNum;
}

void
Visual::SetPrimitiveInstancingNum(size_t primitiveInstancingNum)
{
    mPrimitiveInstancingNum = primitiveInstancingNum;
}
}
