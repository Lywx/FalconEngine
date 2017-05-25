#include <FalconEngine/Graphics/Effect/BitmapFontEffect.h>

#include <FalconEngine/Graphics/Renderer/Font/Font.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(BitmapFontEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFontEffect::BitmapFontEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/BitmapFont.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/BitmapFont.frag.glsl");

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

BitmapFontEffect::~BitmapFontEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
std::shared_ptr<VisualEffectInstance>
BitmapFontEffect::CreateInstance(Visual *visual, const Font *font, const Handedness *handedness, int viewportWidth, int viewportHeight) const
{
    auto visualEffectInstance = CreateSetInstance(visual);
    InitializeInstance(visualEffectInstance.get(), font, handedness, viewportWidth, viewportHeight);

    auto vertexFormat = GetVertexFormat();
    visual->SetVertexFormat(vertexFormat);
    auto vertexGroup = make_shared<VertexGroup>();
    auto vertexBuffer = visual->GetMesh()->GetPrimitive()->GetVertexBuffer();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
    visual->SetVertexGroup(vertexGroup);
    return visualEffectInstance;
}

std::shared_ptr<VertexFormat>
SignedDistancedFieldFontEffectCreateVertexFormat()
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

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
BitmapFontEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance *visualEffectInstance,
                                     _IN_     const Font     *font,
                                     _IN_     const Handedness     *handedness,
                                     _IN_     int                   viewportWidth,
                                     _IN_     int                   viewportHeight) const
{
    visualEffectInstance->SetShaderUniform(0, ShareConstant<Matrix4f>("ProjectionTransform",
                                           handedness->CreateOrthogonal(1, float(viewportWidth), 0, float(viewportHeight), -1.0f, 1.0f)));

    // NOTE(Wuxiang): You don't need to set the texture sampler uniform because
    // they are predefined in the fe_Texture.glsl as #include extension.

    visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Font), font->GetTexture());
    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Font), font->GetSampler());
}

std::shared_ptr<VertexFormat>
BitmapFontEffect::GetVertexFormat() const
{
    static std::shared_ptr<VertexFormat> sVertexFormat = SignedDistancedFieldFontEffectCreateVertexFormat();
    return sVertexFormat;
}

}
