#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>

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

    // TODO(Wuxiang 2017-01-22 10:41): Fix this with a default shader storage.
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BitmapFont.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BitmapFont.frag.glsl");

    shader->PushAttribute(0, "Position", ShaderVertexAttributeType::FloatVec2, false);
    shader->PushAttribute(1, "TexCoord", ShaderVertexAttributeType::FloatVec2, false);
    shader->PushAttribute(2, "FontColor", ShaderVertexAttributeType::FloatVec4, false);
    shader->PushAttribute(3, "FontWidth", ShaderVertexAttributeType::Float, false);
    shader->PushAttribute(4, "FontEdge", ShaderVertexAttributeType::Float, false);
    shader->PushAttribute(5, "FontPage", ShaderVertexAttributeType::Float, false);

    shader->PushUniform("Projection", ShaderUniformType::FloatMat4);
    shader->PushUniform("Texture", ShaderUniformType::Int);

    // Prepare text batcher and text buffer
    glGenVertexArrays(1, &mTextShaderDefaultVao);
    glBindVertexArray(mTextShaderDefaultVao);

    glBindBuffer(GL_ARRAY_BUFFER, mTextShaderDefaultBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 2 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 4 * sizeof(float)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 8 * sizeof(float)));
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 9 * sizeof(float)));
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET(10 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
VisualEffectInstance *
BitmapFontEffect::CreateInstance(VisualEffectInstance *instance, const BitmapFont *font, int width, int height) const
{
    auto projection = mCameraHandedness->CreateOrthogonal(float(width), float(height), 1.0f, 1000.0f);
    instance->SetShaderUniform(0, ShareConstant<Matrix4f>("Projection", projection));
    instance->SetShaderTexture(0, 0, font->GetTexture());
    instance->SetShaderSampler(0, 0, font->GetSampler());

    return instance;
}

VisualEffectInstance *
BitmapFontEffect::CreateInstance(const BitmapFont *font, int width, int height)
{

}

}
