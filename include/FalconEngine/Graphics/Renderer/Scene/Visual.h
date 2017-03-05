#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

class Primitive;
using PrimitiveSharedPtr = std::shared_ptr<Primitive>;

class VisualEffectInstance;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

// @summary This class governs the all the information the user would like to draw
// a set of primitives. Visual effect instance in the Visual class represents all
// uniforms, textures, samplers etc used in the draw calls. However, the effect
// instance is not required as long as you are providing another effect instance
// during draw request.
//
// @remark If you would need to process primitive in different ways, the Visual
// class is the ideal place to differentiate when drawing -- transparency, etc
// special treatment information should be stored in this class.
class Visual : public Spatial
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Visual(PrimitiveSharedPtr primitive);
    virtual ~Visual();

public:
    VisualEffectInstance *
    GetEffectInstance() const;

    void
    SetEffectInstance(VisualEffectInstanceSharedPtr effectInstance);

    const Primitive *
    GetPrimitive() const;

    void
    SetPrimitive(PrimitiveSharedPtr primitives);

protected:
    VisualEffectInstanceSharedPtr mEffectInstance;
    PrimitiveSharedPtr            mPrimitive;
};

}
