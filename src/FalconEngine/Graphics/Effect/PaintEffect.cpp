#include <FalconEngine/Graphics/Effect/PaintEffect.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(PaintEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PaintEffect::PaintEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Paint.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Paint.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
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

PaintEffect::~PaintEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PaintEffect::CreateInstance(Node *node, Color color) const
{
    using namespace placeholders;

    TraverseLevelOrder(node, std::bind([this, color](Visual * visual)
    {
        auto visualEffectInstance = CreateSetInstance(visual);
        InitializeInstance(visualEffectInstance.get(), color);

        // Set up visual.
        auto vertexFormat = GetVertexFormat();
        visual->SetVertexFormat(vertexFormat);
        auto vertexBuffer = visual->GetMesh()->GetPrimitive()->GetVertexBuffer();
        auto vertexGroup = std::make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
        visual->SetVertexGroup(vertexGroup);
    }, _1));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
CreateVertexFormat()
{
    auto vertexFormat = make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

std::shared_ptr<VertexFormat>
PaintEffect::GetVertexFormat() const
{
    static auto sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

void
PaintEffect::InitializeInstance(
    _IN_OUT_ VisualEffectInstance *visualEffectInstance,
    _IN_     Color                 color) const
{
    SetShaderUniformAutomaticModelViewProjectionTransform(visualEffectInstance, 0, "ModelViewProjectionTransform");

    visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector4f>("Color", bind([color]
    {
        return Vector4f(color);
    })));
}

}
