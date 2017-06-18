#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>
#include <vector>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture3d.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformManual.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>


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
//
// @remark It is encourage to write visual effect by introducing an accompanying
// visual effect params class. That class is used to store parameters of visual
// effect so that in editor you could inspect all of effect the visual is binded
// with. This way you could also avoid some mess for effect memory management,
// because you could guarantee the effect params is kept safely when it is binded
// to the visual by using std::shared_ptr.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API VisualEffect : public Object
{
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

protected:
    /************************************************************************/
    /* Effect Instancing Utility                                            */
    /************************************************************************/
    // @remark Force derived class to implement visual based instancing method.
    // Derived classes could use FALCON_ENGINE_EFFECT_IMPLEMENT macro to implement
    // this method.
    virtual std::shared_ptr<VisualEffectInstance>
    CreateInstance() const = 0;

    void
    CheckVertexFormatCompatible(Visual *visual) const;

    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const = 0;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const = 0;

    // @remark You don't need to worry about the lifetime of returned visual effect
    // instance. It is managed by the Visual class using shared_ptr.
    template <typename T>
    std::shared_ptr<VisualEffectInstance>
    InstallInstance(Visual *visual, std::shared_ptr<T> params) const
    {
        static_assert(std::is_base_of<VisualEffectParams, T>::value, "Params must derive from VisualEffectParams");

        FALCON_ENGINE_CHECK_NULLPTR(params);

        // NOTE(Wuxiang): Must check the vertex format is compatible or the vertex
        // data might be passed unexpectedly.
        CheckVertexFormatCompatible(visual);

        // NOTE(Wuxiang): Assume the user would correctly set up vertex group
        // because there is no reliable to test vertex group is compatible
        // with vertex format.

        auto instance = CreateInstance();
        visual->PushEffectInstance(instance);
        visual->PushEffectParams(params);

        return instance;
    }

    void
    TraverseLevelOrder(Node *node, std::function<void(Visual *visual)> visit) const;

    /************************************************************************/
    /* Shader Uniform Utility                                               */
    /************************************************************************/
    void
    SetShaderUniformAutomaticModelTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

    void
    SetShaderUniformAutomaticModelViewTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

    void
    SetShaderUniformAutomaticModelViewProjectionTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

    void
    SetShaderUniformAutomaticViewProjectionTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

    void
    SetShaderUniformAutomaticNormalTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

    void
    SetShaderUniformAutomaticScreenTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const;

protected:
    std::vector<std::unique_ptr<VisualEffectPass>> mEffectPassList; // Passes contained in this effect.
};
#pragma warning(default: 4251)

#define FALCON_ENGINE_EFFECT_DECLARE(klass) \
private: \
    static std::shared_ptr<klass> GetEffect() \
{ \
    static auto sVisualEffect = std::make_shared<klass>(); \
    return sVisualEffect; \
} \
protected: \
    virtual std::shared_ptr<FalconEngine::VisualEffectInstance> \
    CreateInstance() const override;

#define FALCON_ENGINE_EFFECT_IMPLEMENT(klass) \
std::shared_ptr<FalconEngine::VisualEffectInstance> \
klass::CreateInstance() const \
{ \
    auto visualEffectInstance = std::make_shared<FalconEngine::VisualEffectInstance>(GetEffect()); \
    return visualEffectInstance; \
}

}
