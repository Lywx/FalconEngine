#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveTriangles::PrimitiveTriangles(
    const std::shared_ptr<VertexFormat>& vertexFormat,
    const std::shared_ptr<VertexGroup>& vertexGroup,
    const std::shared_ptr<IndexBuffer>& indexBuffer,
    PrimitiveType type) :
    Primitive(type, vertexFormat, vertexGroup, indexBuffer)
{
    auto isTriangleType = type == PrimitiveType::Triangle
                          || type == PrimitiveType::TriangleStrip
                          || type == PrimitiveType::TriangleFan;

    if (!isTriangleType)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Primitive type is not triangle type.");
    }
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
    switch (mType)
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
