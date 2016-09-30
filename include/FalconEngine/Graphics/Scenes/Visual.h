#pragma once

#include <FalconEngine/Graphics/Scenes/Spatial.h>
#include <FalconEngine/Graphics/Shaders/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Resources/IndexBuffer.h>

namespace FalconEngine {

// This class contains information about how the renderer would draw the visual
// element.
enum class VisualPrimitiveType
{
    NONE,

    POINTS,
    LINES,
    TRIANGLES,
    TRIANGLE_STRIP,

    ENUM_COUNT
};

class Visual : public Spatial
{
protected:

    Visual(VisualPrimitiveType primitiveType = VisualPrimitiveType::NONE);

public:

    ~Visual();

    VisualPrimitiveType PrimitiveType;

    //inline void SetVertexFormat(VertexFormat *vformat);
    //inline const VertexFormat *GetVertexFormat() const;
    //inline VertexFormat *GetVertexFormat();

    //inline void SetVertexBuffer(VertexBuffer *vbuffer);
    //inline const VertexBuffer *GetVertexBuffer() const;
    //inline VertexBuffer *GetVertexBuffer();

    //inline void SetIndexBuffer(IndexBuffer *ibuffer);
    //inline const IndexBuffer *GetIndexBuffer() const;
    //inline IndexBuffer *GetIndexBuffer();

    inline const Bound& GetModelBound() const;
    inline Bound& GetModelBound();

    //// Access to the visual effect for drawing the object.
    //inline void SetEffectInstance(VisualEffectInstance *effect);
    //inline VisualEffectInstance *GetEffectInstance() const;

};

}
