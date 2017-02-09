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

Visual::Visual(PrimitiveType primitiveType, VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer) :
    Primitives(primitiveType, vertexBuffer, indexBuffer)
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

}
