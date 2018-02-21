#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <vector>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

class Camera;

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
//
// @remark It is encourage to write visual effect by introducing an accompanying
// visual effect params class. That class is used to store parameters of visual
// effect so that in editor you could inspect all of effect the visual is binded
// with. This way you could also avoid some mess for effect memory management,
// because you could guarantee the effect params is kept safely when it is binded
// to the visual by using std::shared_ptr.
FALCON_ENGINE_CLASS_BEGIN VisualEffect :
public std::enable_shared_from_this<VisualEffect>
{
protected:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualEffect();
    VisualEffect(const VisualEffect&) = delete;
    VisualEffect& operator=(const VisualEffect&) = delete;

public:
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

protected:
    /************************************************************************/
    /* Effect Instancing Utility                                            */
    /************************************************************************/
    std::shared_ptr<const VisualEffect>
    GetEffect() const;

    std::shared_ptr<VisualEffect>
    GetEffect();

    // @remark Force derived class to implement visual based instancing method.
    // Derived classes could use FALCON_ENGINE_EFFECT_GLOBAL_IMPLEMENT macro to
    // implement this method.
    std::shared_ptr<VisualEffectInstance>
    CreateInstance();

    void
    CheckVertexFormatCompatible(const Visual * visual) const;

    void
    CheckVertexGroupCompatible(Visual * visual) const;

    // @remark You don't need to worry about the lifetime of returned visual effect
    // instance. It is managed by the Visual class using shared_ptr.
    template <typename T>
    std::shared_ptr<VisualEffectInstance>
    InstallInstance(Visual * visual, const std::shared_ptr<T>& params)
    {
        static_assert(std::is_base_of<VisualEffectParams, T>::value, "Params must derive from VisualEffectParams");

        FALCON_ENGINE_CHECK_NULLPTR(params);

        // NOTE(Wuxiang): Must check the vertex format is compatible or the vertex
        // data might be passed unexpectedly.
        CheckVertexFormatCompatible(visual);

        // NOTE(Wuxiang): Must check the user have correctly set up vertex
        // group that is compatible with newly inserted vertex format.
        CheckVertexGroupCompatible(visual);

        auto instance = CreateInstance();
        visual->PushEffectInstance(instance);
        visual->PushEffectParams(params);

        return instance;
    }

    void
    TraverseLevelOrder(Node * node, std::function<void(Visual *visual)> visit) const;

    /************************************************************************/
    /* Shader Uniform Buffer Utility                                        */
    /************************************************************************/

    /************************************************************************/
    /* Shader Uniform Utility                                               */
    /************************************************************************/
    void
    SetUniformAutomaticModelTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

    void
    SetUniformAutomaticModelViewTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

    void
    SetUniformAutomaticModelViewProjectionTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

    void
    SetUniformAutomaticViewProjectionTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

    void
    SetUniformAutomaticNormalTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

    void
    SetUniformAutomaticScreenTransform(VisualEffectInstance * visualEffectInstance, int passIndex, const std::string & uniformName) const;

protected:
    // Passes contained in this effect.
    std::vector<std::unique_ptr<VisualEffectPass>> mEffectPassList;
};
FALCON_ENGINE_CLASS_END

#define FALCON_ENGINE_EFFECT_DECLARE(klass)
#define FALCON_ENGINE_EFFECT_IMPLEMENT(klass)

}
