#include <FalconEngine/Graphics/Effect/DebugEffect.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffect::DebugEffect(bool depthTestEnabled)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Debug.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Debug.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = true;
    blendState->mSourceFactor = BlendSourceFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendDestinationFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mTestEnabled = depthTestEnabled;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = false;
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
DebugEffect::CreateInstance(Visual *visual, std::shared_ptr<DebugEffectParams> params) const
{
    auto instance = InstallInstance(visual, params);
    InitializeInstance(instance.get(), params);
}

std::shared_ptr<VertexFormat>
DebugEffect::GetVertexFormat() const
{
    static shared_ptr<VertexFormat> sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
DebugEffect::CreateVertexFormat() const
{
    auto vertexFormat = std::make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

void
DebugEffect::InitializeInstance(VisualEffectInstance *instance, std::shared_ptr<DebugEffectParams> params) const
{
    SetShaderUniformAutomaticModelViewTransform(instance, 0, "ViewProjectionTransform");
}

}
