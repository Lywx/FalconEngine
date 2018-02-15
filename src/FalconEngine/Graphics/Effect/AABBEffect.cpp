#include <FalconEngine/Graphics/Effect/AabbEffect.h>

#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(AabbEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AabbEffect::AabbEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Aabb.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Aabb.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = true;
    blendState->mSourceFactor = BlendFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mEnabled = true;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = true;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

AabbEffect::~AabbEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
std::shared_ptr<VisualEffectInstance>
AabbEffect::CreateInstance(Visual *visual, const std::shared_ptr<AabbEffectParams>& params)
{
    auto instance = InstallInstance(visual, params);

    // NOTE(Wuxiang): Don't need to initialize any instance because all the
    // parameters are in the vertex buffer.

    return instance;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
AabbEffect::CreateVertexFormat() const
{
    auto vertexFormat = std::make_shared<VertexFormat>();

    // NOTE(Wuxiang): Fixed vertex data. No instancing.
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);

    // NOTE(Wuxiang): Each bounding box has only one color, used with instancing.
    vertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 1, 1);

    // NOTE(Wuxiang): Transform matrix would use instancing. Different transformation
    // buffer would be used to provide the matrix data.
    vertexFormat->PushVertexAttribute(2, "ModelViewProjectionTransform", VertexAttributeType::FloatVec4, false, 1, 1);

    // NOTE(Wuxiang): The name is not meant to be valid for mat4.
    vertexFormat->PushVertexAttribute(3, "", VertexAttributeType::FloatVec4, false, 1, 1);
    vertexFormat->PushVertexAttribute(4, "", VertexAttributeType::FloatVec4, false, 1, 1);
    vertexFormat->PushVertexAttribute(5, "", VertexAttributeType::FloatVec4, false, 1, 1);
    vertexFormat->FinishVertexAttribute();

    return vertexFormat;
}

std::shared_ptr<VertexFormat>
AabbEffect::GetVertexFormatSp() const
{
    static shared_ptr<VertexFormat> sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

}
