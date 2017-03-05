#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(PrimitiveSharedPtr primitive) :
    mPrimitive(primitive)
{
}

Visual::~Visual()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
VisualEffectInstance *
Visual::GetEffectInstance() const
{
    return mEffectInstance.get();
}

void
Visual::SetEffectInstance(VisualEffectInstanceSharedPtr effectInstance)
{
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
    mPrimitive = primitive;
}

}
