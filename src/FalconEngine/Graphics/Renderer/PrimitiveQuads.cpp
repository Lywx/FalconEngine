#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveQuads, PrimitiveTriangles);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveQuads::PrimitiveQuads(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer) :
    PrimitiveTriangles(vertexBuffer, indexBuffer)
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
        return mVertexBuffer->GetElementNum() / 3;
    }
}

}
