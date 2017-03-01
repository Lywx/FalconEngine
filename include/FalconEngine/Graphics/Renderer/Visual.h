#pragma once

#include <FalconEngine/Graphics/Renderer/Primitives.h>

namespace FalconEngine
{

class VisualEffectInstance;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

// @summary This class governs the all the information the user would like to draw
// a set of primitives. Visual effect instance in the Visual class represents all
// uniforms, textures, samplers etc used in the draw calls. However, the effect
// instance is not required as long as you are providing another effect instance
// during draw request.
class Visual : public Primitives
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat);
    Visual(PrimitiveType primitiveType, VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
    virtual ~Visual();

public:
    VisualEffectInstance *
    GetEffectInstance() const;

    void
    SetEffectInstance(VisualEffectInstanceSharedPtr effectInstance);

protected:
    VisualEffectInstanceSharedPtr mEffectInstance;
};

using VisualSharedPtr = std::shared_ptr<Visual>;

}
