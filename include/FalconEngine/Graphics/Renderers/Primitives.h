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
    explicit Primitives(PrimitiveType primitiveType);
    Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat);
    Primitives(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, IndexBufferSharedPtr indexBuffer);
public:
    virtual ~Primitives();

public:
    PrimitiveType
    GetPrimitiveType() const;

    const VertexFormat *
    GetVertexFormat() const;

    int
    GetVertexNum() const
    {
        return mVertexNum;
    }

    const IndexBuffer *
    GetIndexBuffer() const;

protected:

    // NOTE(Wuxiang): This function should be implemented by the derived class
    // and add final keyword in the derived class declaration. This function
    // should be call during the derived class constructor.
    virtual void
    SetPrimitiveNum();

    void
    SetVertexNum(int vertexNum);

protected:
    PrimitiveType         mPrimitiveType;
    VertexFormatSharedPtr mVertexFormat;
    int                   mVertexNum;
    IndexBufferSharedPtr  mIndexBuffer;
};

}
