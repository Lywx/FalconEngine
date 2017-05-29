#include <FalconEngine/Graphics/Effect/FontEffect.h>

#include <FalconEngine/Graphics/Renderer/Font/Font.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(FontEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FontEffect::FontEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Font.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Font.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = true;
    blendState->mSourceFactor = BlendSourceFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendDestinationFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = true;
    cullState->mCounterClockwise = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mTestEnabled = false;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = false;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

FontEffect::~FontEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
FontEffect::CreateInstance(Visual *visual, std::shared_ptr<FontEffectParams> params) const
{
    FALCON_ENGINE_CHECK_NULLPTR(params);

    CheckVertexFormatCompatible(visual);

    auto instance = CreateInstance();
    visual->PushEffectInstance(instance);
    visual->PushEffectParams(params);

    InitializeInstance(instance.get(), params);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
FontEffect::CreateVertexFormat() const
{
    auto vertexFormat = std::make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->PushVertexAttribute(1, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->PushVertexAttribute(2, "FontColor", VertexAttributeType::FloatVec4, false, 0);
    vertexFormat->PushVertexAttribute(3, "FontWidth", VertexAttributeType::Float, false, 0);
    vertexFormat->PushVertexAttribute(4, "FontEdge", VertexAttributeType::Float, false, 0);
    vertexFormat->PushVertexAttribute(5, "FontPage", VertexAttributeType::Float, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

std::shared_ptr<VertexFormat>
FontEffect::GetVertexFormat() const
{
    static shared_ptr<VertexFormat> sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

void
FontEffect::InitializeInstance(
    _IN_OUT_ VisualEffectInstance             *instance,
    _IN_     std::shared_ptr<FontEffectParams> params) const
{
    FALCON_ENGINE_CHECK_NULLPTR(params->mFont);
    FALCON_ENGINE_CHECK_NULLPTR(params->mHandedness);

    instance->SetShaderUniform(0, ShareConstant<Matrix4f>("ProjectionTransform",
                               params->mHandedness->CreateOrthogonal(
                                   0, float(params->mViewportWidth),
                                   0, float(params->mViewportHeight), -1.0f, 1.0f)));

    // NOTE(Wuxiang): You don't need to set the texture sampler uniform because
    // they are predefined in the fe_Texture.glsl as #include extension.
    instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Font), params->mFont->GetTexture());
    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Font), params->mFont->GetSampler());
}

}
