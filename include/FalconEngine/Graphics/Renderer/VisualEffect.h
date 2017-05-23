#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

#include <FalconEngine/Core/Object.h>
#include <functional>

namespace FalconEngine
{

class Node;

class Shader;

class VertexFormat;

class Visual;
class VisualEffectInstance;
class VisualEffectPass;

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

// @summary Represents a factory of generating visual effect instance. This class
// would not contain any asset. All it has is renderer state metadata used in the
// renderer.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VisualEffect : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffect();
    VisualEffect(const VisualEffect&) = delete;
    VisualEffect& operator=(const VisualEffect&) = delete;

    // @remark You should not manually call destructor of VisualEffect. The
    // destructor would be called by shared_ptr.
    virtual ~VisualEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    InsertPass(std::unique_ptr<VisualEffectPass> pass);

    int
    GetPassNum() const;

    const VisualEffectPass *
    GetPass(int passIndex) const;

    VisualEffectPass *
    GetPass(int passIndex);

    Shader *
    GetShader(int passIndex);

    const BlendState *
    GetBlendState(int passIndex) const;

    const CullState *
    GetCullState(int passIndex) const;

    const DepthTestState *
    GetDepthTestState(int passIndex) const;

    const OffsetState *
    GetOffsetState(int passIndex) const;

    const StencilTestState *
    GetStencilTestState(int passIndex) const;

    const WireframeState *
    GetWireframeState(int passIndex) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const;

protected:
    void
    CheckEffectCompatible(VisualEffectInstance *instance) const;

    void
    CheckEffectSame(VisualEffect *effect) const;

    void
    TraverseVisualLevelOrder(Node *node, std::function<void(Visual *)> visualOperation);

protected:
    std::vector<std::unique_ptr<VisualEffectPass>> mPassList; // Passes contained in this effect.
};
#pragma warning(default: 4251)

}
