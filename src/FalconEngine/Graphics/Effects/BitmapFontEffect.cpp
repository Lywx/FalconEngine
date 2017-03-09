#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>

#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFont.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(BitmapFontEffect, VisualEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFontEffect::BitmapFontEffect(const Handedness *handedness) :
    mCameraHandedness(handedness)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BitmapFont.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BitmapFont.frag.glsl");

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
void
BitmapFontEffect::CreateInstance(VisualEffectInstance *instance, const BitmapFont *font, int width, int height) const
{
    CheckEffectCompatible(instance);

    auto projection = mCameraHandedness->CreateOrthogonal(0, float(width), 0, float(height), -1.0f, 1.0f);
    instance->SetShaderUniform(0, ShareConstant<Matrix4f>("ProjectionTransform", projection));

    // NOTE(Wuxiang): You don't need to set the texture sampler uniform because
    // they are predefined in the fe_Texture.glsl as #include extension.

    instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Font), font->GetTexture());
    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Font), font->GetSampler());
}

VertexFormatSharedPtr
BitmapFontEffect::CreateVertexFormat()
{
    static VertexFormatSharedPtr sVertexFormat;
    if (sVertexFormat == nullptr)
    {
        sVertexFormat = std::make_shared<VertexFormat>();
        sVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec2, false, 0);
        sVertexFormat->PushVertexAttribute(1, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
        sVertexFormat->PushVertexAttribute(2, "FontColor", VertexAttributeType::FloatVec4, false, 0);
        sVertexFormat->PushVertexAttribute(3, "FontWidth", VertexAttributeType::Float, false, 0);
        sVertexFormat->PushVertexAttribute(4, "FontEdge", VertexAttributeType::Float, false, 0);
        sVertexFormat->PushVertexAttribute(5, "FontPage", VertexAttributeType::Float, false, 0);
        sVertexFormat->FinishVertexAttribute();
    }

    return sVertexFormat;
}

}
