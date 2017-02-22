#include <FalconEngine/Graphics/Renderers/Visual.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Visual, Primitives);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat) :
    Primitives(primitiveType, vertexFormat)
{
}

Visual::Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    Primitives(primitiveType, vertexFormat, vertexGroup, indexBuffer)
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
