#pragma once

#include <FalconEngine/Graphics/Bound.h>
#include <FalconEngine/Graphics/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Scenes/Spatial.h>
#include <FalconEngine/Graphics/Shaders/VisualEffectInstance.h>

namespace FalconEngine {

// @Summary: This class contains information about how the renderer would draw the visual
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

// @Summary: This class .
class Visual : public Spatial
{
protected:

    Visual(VisualPrimitiveType primitiveType = VisualPrimitiveType::NONE);

public:

    virtual ~Visual();

    VisualPrimitiveType     PrimitiveType;
    VertexFormatPtr         VertexFormat;
    VertexBufferPtr         VertexBuffer;
    IndexBufferPtr          IndexBuffer;
    VisualEffectInstancePtr VisualEffectInstance;

    Bound                   ModelBound;

protected:

    virtual void UpdateWorldBound() override;
    virtual void UpdateModelBound();

};

typedef std::shared_ptr<Visual> VisualPtr;

}
