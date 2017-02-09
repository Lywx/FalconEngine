#pragma once

#include <FalconEngine/Graphics/Renderers/Primitives.h>

namespace FalconEngine
{

// @summary This class governs the all the information the user would like to draw
// a set of primitives. Visual effect instance in the Visual class represents all
// uniforms, textures, samplers etc used in the draw calls.
class Visual : public Primitives
{
    FALCON_ENGINE_RTTI_DECLARE;

protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Visual(PrimitiveType primitiveType);
    Visual(PrimitiveType primitiveType, VertexBufferSharedPtr vertexBuffer, IndexBufferSharedPtr indexBuffer);
    virtual ~Visual();

public:
    VisualEffectInstance *
    GetEffectInstance() const;

protected:
    VisualEffectInstanceSharedPtr mEffectInstance;
};

}
