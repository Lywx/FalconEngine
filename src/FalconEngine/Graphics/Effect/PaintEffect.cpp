#include <FalconEngine/Graphics/Effect/PaintEffect.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(PaintEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PaintEffect::PaintEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                           "Content/Shader/Paint.vert.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                           "Content/Shader/Paint.vert.glsl");
#endif
    shader->PushShaderFile(ShaderType::FragmentShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                           "Content/Shader/Paint.frag.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                           "Content/Shader/Paint.frag.glsl");
#endif

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto shaderVertexFormat = make_shared<VertexFormat>(shader);
    shaderVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    shaderVertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 1);
    shaderVertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 2);
    shaderVertexFormat->FinishVertexAttribute();
    pass->SetShaderVertexFormat(shaderVertexFormat);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    cullState->mCounterClockwise = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mEnabled = false;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = false;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

PaintEffect::~PaintEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PaintEffect::CreateInstance(_IN_OUT_ Node                                     *node,
                            _IN_     const std::shared_ptr<PaintEffectParams>& params)
{
    FALCON_ENGINE_CHECK_NULLPTR(params);

    using namespace placeholders;

    TraverseLevelOrder(node, std::bind([&, this](Visual * visual)
    {
        auto instance = InstallInstance(visual, params);
        InitializeInstance(instance.get(), params);
    }, _1));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PaintEffect::InitializeInstance(
    _IN_OUT_ VisualEffectInstance *instance,
    _IN_     const std::shared_ptr<PaintEffectParams>& params) const
{
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::PaintBufferData, "PaintBuffer", = )
    {
        data->mModelViewProjectionTransform = camera->GetViewProjection() * visual->mWorldTransform;
        data->mColor = Vector4f(params->mColor);
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(0, GetShaderMask(ShaderType::VertexShader));
}

}
