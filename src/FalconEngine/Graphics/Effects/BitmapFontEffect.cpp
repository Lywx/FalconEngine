#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(BitmapFontEffect, VisualEffect);

VertexFormatSharedPtr
BitmapFontEffect::GetVertexFormatInstance()
{
    if (sVertexFormat == nullptr)
    {
        sVertexFormat = std::make_shared<VertexFormat>();
        sVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec2, false, 0);
        sVertexFormat->PushVertexAttribute(1, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
        sVertexFormat->PushVertexAttribute(2, "FontColor", VertexAttributeType::FloatVec4, false, 0);
        sVertexFormat->PushVertexAttribute(3, "FontWidth", VertexAttributeType::Float, false, 0);
        sVertexFormat->PushVertexAttribute(4, "FontEdge", VertexAttributeType::Float, false, 0);
        sVertexFormat->PushVertexAttribute(5, "FontPage", VertexAttributeType::Float, false, 0);
    }

    return sVertexFormat;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFontEffect::BitmapFontEffect(const Handedness *handedness) :
    mCameraHandedness(handedness)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BitmapFont.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BitmapFont.frag.glsl");

    shader->PushUniform("Projection", ShaderUniformType::FloatMat4);
    shader->PushUniform("Texture", ShaderUniformType::Int);

    //shader->

    auto pass = make_unique<VisualPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = true;
    blendState->mSourceFactor = BlendSourceFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendDestinationFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    pass->SetCullState(make_unique<CullState>());

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mTestEnabled = false;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique< OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());
    pass->SetWireframeState(make_unique<WireframeState>());

    InsertPass(move(pass));
}

BitmapFontEffect::~BitmapFontEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BitmapFontEffect::CreateInstance(VisualEffectInstance *instance, const BitmapFont *font, int width, int height) const
{
    CheckEffectCompatible(instance);

    auto projection = mCameraHandedness->CreateOrthogonal(float(width), float(height), 1.0f, 1000.0f);
    instance->SetShaderUniform(0, ShareConstant<Matrix4f>("Projection", projection));

    // TODO(Wuxiang): Should I change the texture unit?
    instance->SetShaderTexture(0, 0, font->GetTexture());
    instance->SetShaderSampler(0, 0, font->GetSampler());
}

VisualEffectInstanceSharedPtr
BitmapFontEffect::CreateInstance(const BitmapFont *font, int width, int height)
{
    auto instance = new VisualEffectInstance(GetSharedPtr());
    CreateInstance(instance, font, width, height);
    return VisualEffectInstanceSharedPtr(instance);
}

}
