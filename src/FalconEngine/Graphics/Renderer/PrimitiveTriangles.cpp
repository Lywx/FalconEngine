#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveTriangles, Primitive);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveTriangles::PrimitiveTriangles(VertexFormatSharedPtr vertexFormat) :
    Primitive(PrimitiveType::Triangle, vertexFormat)
{
}

PrimitiveTriangles::PrimitiveTriangles(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup) :
    PrimitiveTriangles(vertexFormat, vertexGroup, nullptr)
{
}

PrimitiveTriangles::PrimitiveTriangles(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer) :
    Primitive(PrimitiveType::Triangle, vertexFormat, vertexGroup, indexBuffer)
{
}

PrimitiveTriangles::~PrimitiveTriangles()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
size_t
PrimitiveTriangles::GetTriangleNum() const
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
