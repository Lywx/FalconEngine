#include <FalconEngine/Graphics/Effect/AABBBoundingBoxEffect.h>

#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(AABBBoundingBoxEffect, VisualEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABBBoundingBoxEffect::AABBBoundingBoxEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BoundingBox.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BoundingBox.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
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
void
AABBBoundingBoxEffect::CreateInstance(VisualEffectInstance *instance, const Camera *camera) const
{
    CheckEffectCompatible(instance);
}

VertexFormatSharedPtr
AABBBoundingBoxEffect::CreateVertexFormat()
{
    static VertexFormatSharedPtr sVertexFormat;
    if (sVertexFormat == nullptr)
    {
        sVertexFormat = std::make_shared<VertexFormat>();

        // NOTE(Wuxiang): Fixed vertex data. No instancing.
        sVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);

        // NOTE(Wuxiang): Each bounding box has only one color, used with instancing.
        sVertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 1, 1);

        // NOTE(Wuxiang): Transform matrix would use instancing. Different transformation
        // buffer would be used to provide the matrix data.
        sVertexFormat->PushVertexAttribute(2, "ModelViewProjectionTransform", VertexAttributeType::FloatVec4, false, 1, 1);

        // NOTE(Wuxiang): The name is not meant to be valid for mat4.
        sVertexFormat->PushVertexAttribute(3, "", VertexAttributeType::FloatVec4, false, 1, 1);
        sVertexFormat->PushVertexAttribute(4, "", VertexAttributeType::FloatVec4, false, 1, 1);
        sVertexFormat->PushVertexAttribute(5, "", VertexAttributeType::FloatVec4, false, 1, 1);
        sVertexFormat->FinishVertexAttribute();
    }

    return sVertexFormat;
}
}
