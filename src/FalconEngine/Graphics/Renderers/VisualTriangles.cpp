#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualTriangles, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualTriangles::VisualTriangles(VertexFormatSharedPtr vertexFormat) :
    Visual(PrimitiveType::Triangle, vertexFormat)
{
    // NOTE(Wuxiang): The user for this constructor should be responsible for
    // correctly initializing the mTriangleNum.
}

VisualTriangles::VisualTriangles(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    Visual(PrimitiveType::Triangle, vertexFormat, vertexGroup, indexBuffer)
{
}

VisualTriangles::~VisualTriangles()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
VisualTriangles::GetTriangleNum() const
{
    if (mIndexBuffer)
    {
        return mIndexBuffer->GetElementNum() / 3;
    }
    else
    {
        return mVertexGroup->GetVertexNum() / 3;
    }
}

}
