#include <FalconEngine/Graphics/Renderers/Visual.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Primitives);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(PrimitiveType primitiveType) :
    Primitives(primitiveType)
{
}

Visual::Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat) :
    Primitives(primitiveType, vertexFormat)
{
}

Visual::Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, IndexBufferSharedPtr indexBuffer) :
    Primitives(primitiveType, vertexFormat, indexBuffer)
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

}
