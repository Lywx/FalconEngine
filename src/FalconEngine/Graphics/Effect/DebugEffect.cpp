#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBufferManual.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffectParams::DebugEffectParams() :
    mCamera(nullptr)
{
}

FALCON_ENGINE_EFFECT_IMPLEMENT(DebugEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffect::DebugEffect(bool depthTestEnabled)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                           "Content/Shader/Debug.vert.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                           "Content/Shader/Debug.vert.glsl");
#endif

    shader->PushShaderFile(ShaderType::FragmentShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                           "Content/Shader/Debug.frag.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                           "Content/Shader/Debug.frag.glsl");
#endif

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto shaderVertexFormat = std::make_shared<VertexFormat>(shader);
    shaderVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    shaderVertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 0);
    shaderVertexFormat->FinishVertexAttribute();
    pass->SetShaderVertexFormat(shaderVertexFormat);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    blendState->mSourceFactor = BlendFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mEnabled = depthTestEnabled;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = true;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

DebugEffect::~DebugEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
DebugEffect::CreateInstance(Visual *visual, const std::shared_ptr<DebugEffectParams>& params)
{
    auto instance = InstallInstance(visual, params);
    InitializeInstance(instance.get(), params);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
DebugEffect::InitializeInstance(
    VisualEffectInstance              *instance,
    std::shared_ptr<DebugEffectParams> params) const
{

    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::DebugTransformBufferData, "TransformBuffer", = )
    {
        data->mViewProjectionTransform = params->mCamera ? params->mCamera->GetViewProjection() : Matrix4f::Zero;
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(GetShaderMask(ShaderType::VertexShader));
}

}
