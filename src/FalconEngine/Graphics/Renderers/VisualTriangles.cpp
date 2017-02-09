#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualTriangles, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualTriangles::VisualTriangles(VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer) :
    Visual(PrimitiveType::Triangle, vertexBuffer, indexBuffer)
{
    if (mIndexBuffer)
    {
        mTriangleNum = indexBuffer->mElementNum / 3;
    }
    else
    {
        mTriangleNum = vertexBuffer->mElementNum / 3;
    }
}

VisualTriangles::~VisualTriangles()
{
}

}
