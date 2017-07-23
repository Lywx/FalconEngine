#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveQuads::PrimitiveQuads(
    const std::shared_ptr<VertexFormat>& vertexFormat,
    const std::shared_ptr<VertexGroup>& vertexGroup,
    const std::shared_ptr<IndexBuffer>& indexBuffer) :
    PrimitiveTriangles(vertexFormat, vertexGroup, indexBuffer)
{
}

PrimitiveQuads::~PrimitiveQuads()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
size_t
PrimitiveQuads::GetQuadNum() const
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
