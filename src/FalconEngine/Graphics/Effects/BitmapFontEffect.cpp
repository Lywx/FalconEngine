#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>

#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFont.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/States/BlendState.h>
#include <FalconEngine/Graphics/Renderer/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/States/CullState.h>
#include <FalconEngine/Graphics/Renderer/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/States/WireframeState.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(BitmapFontEffect, VisualEffect);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
VertexFormatSharedPtr
BitmapFontEffect::CreateVertexFormat()
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
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFontEffect::BitmapFontEffect(const Handedness *handedness) :
    mCameraHandedness(handedness)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BitmapFont.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BitmapFont.frag.glsl");

    shader->PushUniform("ProjectionTransform", ShaderUniformType::FloatMat4);

    auto pass = make_unique<VisualPass>();
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

}
