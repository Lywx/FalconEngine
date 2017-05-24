#include <FalconEngine/Graphics/Effect/AABBBoundingBoxEffect.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(AABBBoundingBoxEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABBBoundingBoxEffect::AABBBoundingBoxEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/AABBBoundingBoxInstancing.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/AABBBoundingBoxInstancing.frag.glsl");

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
    depthTestState->mTestEnabled = true;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = true;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

AABBBoundingBoxEffect::~AABBBoundingBoxEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
std::shared_ptr<VisualEffectInstance>
AABBBoundingBoxEffect::CreateInstance(Visual *visual, std::shared_ptr<VertexBuffer> instanceBuffer) const
{
    auto visualEffectInstance = CreateSetInstance(visual);

    auto vertexFormat = GetVertexFormat();
    visual->SetVertexFormat(vertexFormat);
    auto vertexGroup = make_shared<VertexGroup>();
    auto vertexBuffer = visual->GetMesh()->GetPrimitive()->GetVertexBuffer();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
    vertexGroup->SetVertexBuffer(1, instanceBuffer, 0, vertexFormat->GetVertexBufferStride(1));
    visual->SetVertexGroup(vertexGroup);

    return visualEffectInstance;
}

std::shared_ptr<VertexFormat>
AABBBoundingBoxInstancingEffectCreateVertexFormat()
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
AABBBoundingBoxEffect::GetVertexFormat() const
{
    static std::shared_ptr<VertexFormat> sVertexFormat = AABBBoundingBoxInstancingEffectCreateVertexFormat();
    return sVertexFormat;
}

}
