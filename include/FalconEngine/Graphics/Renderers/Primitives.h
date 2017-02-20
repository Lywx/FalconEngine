#pragma once

#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine
{

enum class PrimitiveType
{
    None,
    Point,
    Line,
    LineStrip,
    Triangle,
    Count,
};

class Primitives : public Spatial
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    Primitives(PrimitiveType primitiveType = PrimitiveType::None);
    Primitives(PrimitiveType primitiveType, VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer);
public:
    virtual ~Primitives();

public:
    const PrimitiveType
    GetPrimitiveType() const;

    const VertexFormat *
    GetVertexFormat() const;

    const IndexBuffer *
    GetIndexBuffer() const;

protected:
    PrimitiveType         mPrimitiveType;
    VertexFormatSharedPtr mVertexFormat;
    IndexBufferSharedPtr  mIndexBuffer;
};

}
