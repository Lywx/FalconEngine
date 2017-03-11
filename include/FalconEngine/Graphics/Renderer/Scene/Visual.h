#pragma once

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>

namespace FalconEngine
{

class BoundingBox;

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

protected:
    Visual();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const BoundingBox *
    GetBoundingBox() const;

    VisualEffectInstance *
    GetEffectInstance() const;

    void
    SetEffectInstance(VisualEffectInstanceSharedPtr effectInstance);

    const Primitive *
    GetPrimitive() const;

    void
    SetPrimitive(PrimitiveSharedPtr primitives);

    size_t
    GetEffectInstancingNum() const;

    void
    SetEffectInstancingNum(size_t effectInstancingNum);

    void
    UpdateWorldTransform(double elapsed) override;

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    void
    CopyTo(Visual *lhs) const;

    // @remark This method use return type covariance in the class hierarchy.
    // @return The clone of this Visual instance. Grant for no shared ownership.
    virtual Visual *
    GetClone() const override;

protected:
    VisualEffectInstanceSharedPtr mEffectInstance;
    size_t                        mEffectInstancingNum;
    PrimitiveSharedPtr            mPrimitive;
};

}
