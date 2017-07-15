#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveTriangles::PrimitiveTriangles(PrimitiveType primitiveType,
                                       std::shared_ptr<VertexFormat> vertexFormat,
                                       std::shared_ptr<VertexGroup> vertexGroup,
                                       std::shared_ptr<IndexBuffer> indexBuffer) :
    Primitive(primitiveType, vertexFormat, vertexGroup, indexBuffer)
{
    if (primitiveType == PrimitiveType::Triangle
            || primitiveType == PrimitiveType::TriangleStrip
            || primitiveType == PrimitiveType::TriangleFan)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Primitive type is not triangle type.");
    }
}

PrimitiveTriangles::PrimitiveTriangles(std::shared_ptr<VertexFormat> vertexFormat, std::shared_ptr<VertexGroup> vertexGroup, std::shared_ptr<IndexBuffer> indexBuffer) :
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
    switch (mPrimitiveType)
    {
    case PrimitiveType::Triangle:
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

    break;

    case PrimitiveType::TriangleStrip:
    {
        if (mIndexBuffer)
        {
            return mIndexBuffer->GetElementNum() - 2;
        }
        else
        {
            return mVertexGroup->GetVertexNum() - 2;
        }
    }

    break;

    case PrimitiveType::TriangleFan:
    {
        // http://stackoverflow.com/questions/8043923/gl-triangle-fan-explanation
        if (mIndexBuffer)
        {
            return mIndexBuffer->GetElementNum() - 2;
        }
        else
        {
            return mVertexGroup->GetVertexNum() - 2;
        }
    }

    break;

    default:
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("");
    }
}

}
