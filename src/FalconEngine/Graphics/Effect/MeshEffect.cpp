#include <FalconEngine/Graphics/Effect/MeshEffect.h>

#include <FalconEngine/Core/GameEngineGraphics.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(MeshEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MeshEffect::MeshEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Mesh.vert.glsl");
    shader->PushShaderFile(ShaderType::GeometryShader, "Content/Shader/Mesh.geom.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Mesh.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto shaderVertexFormat = std::make_shared<VertexFormat>(shader);
    shaderVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    shaderVertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 1);
    shaderVertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 2);
    shaderVertexFormat->FinishVertexAttribute();
    pass->SetShaderVertexFormat(shaderVertexFormat);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    cullState->mCounterClockwise = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mEnabled = true;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = false;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

MeshEffect::~MeshEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
MeshEffect::CreateInstance(Node *node, const std::shared_ptr<MeshEffectParams>& params)
{
    using namespace placeholders;

    VisualEffect::TraverseLevelOrder(node, std::bind([&, this](Visual * visual)
    {
        auto instance = InstallInstance(visual, params);
        InitializeInstance(instance.get(), visual->GetMesh()->GetMaterialSp(), params);
    }, _1));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
MeshEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance                    *instance,
                               _IN_     const std::shared_ptr<Material>&         material,
                               _IN_     const std::shared_ptr<MeshEffectParams>& params) const
{
    using namespace placeholders;

    // Transform
    SetUniformAutomaticModelViewProjectionTransform(instance, 0, "ModelViewProjectionTransform");
    SetUniformAutomaticModelViewTransform(instance, 0, "ModelViewTransform");
    SetUniformAutomaticNormalTransform(instance, 0, "NormalTransform");
    SetUniformAutomaticScreenTransform(instance, 0, "ScreenTransform");

    // Material
    {
        // Ambient
        instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Ambient",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mAmbientColor);
        }, _1, _2)));

        // Diffuse
        instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Diffuse",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mDiffuseColor);
        }, _1, _2)));

        // Emissive
        instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Emissive",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mEmissiveColor);
        }, _1, _2)));

        // Shininess
        instance->SetUniform(0, ShareUniformAutomatic<float>("fe_Material.Shininess",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return material->mShininess;
        }, _1, _2)));

        // Specular
        instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Specular",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mSpecularColor);
        }, _1, _2)));
    }

    // Light
    {
        instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("AmbientColor",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(params->mAmbientColor);
        }, _1, _2)));

        instance->SetUniform(0, ShareUniformAutomatic<bool>("TextureEnabled",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return params->mTextureEnabled;
        }, _1, _2)));
    }

    // Line
    {
        instance->SetUniform(0, ShareUniformAutomatic<Vector4f>("Line.Color",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector4f(params->mLineColor);
        }, _1, _2)));

        instance->SetUniform(0, ShareUniformAutomatic<float>("Line.Width",
                             std::bind([ = ](const Visual *, const Camera *)
        {
            return params->mLineWidth;
        }, _1, _2)));
    }
}

}
