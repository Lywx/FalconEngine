#include <FalconEngine/Graphics/Effect/MeshEffect.h>

#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>

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

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    cullState->mCounterClockwise = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mTestEnabled = true;
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
MeshEffect::CreateInstance(Node *node, std::shared_ptr<MeshEffectParams> params) const
{
    using namespace placeholders;

    VisualEffect::TraverseLevelOrder(node, std::bind([&, this](Visual * visual)
    {
        auto instance = InstallInstance(visual, params);
        InitializeInstance(instance.get(), visual->GetMesh()->GetMaterial(), params);
    }, _1));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
MeshEffect::CreateVertexFormat() const
{
    auto vertexFormat = std::make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

std::shared_ptr<VertexFormat>
MeshEffect::GetVertexFormat() const
{
    static shared_ptr<VertexFormat> sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

void
MeshEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance             *instance,
                               _IN_     std::shared_ptr<Material>         material,
                               _IN_     std::shared_ptr<MeshEffectParams> params) const
{
    using namespace placeholders;

    // Transform
    SetShaderUniformAutomaticModelViewProjectionTransform(instance, 0, "ModelViewProjectionTransform");
    SetShaderUniformAutomaticModelViewTransform(instance, 0, "ModelViewTransform");
    SetShaderUniformAutomaticNormalTransform(instance, 0, "NormalTransform");
    SetShaderUniformAutomaticScreenTransform(instance, 0, "ScreenTransform");

    // Material
    {
        // Ambient
        instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Ambient",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mAmbientColor);
        }, _1, _2)));

        // Diffuse
        instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Diffuse",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mDiffuseColor);
        }, _1, _2)));

        // Emissive
        instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Emissive",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mEmissiveColor);
        }, _1, _2)));

        // Shininess
        instance->SetShaderUniform(0, ShareAutomatic<float>("fe_Material.Shininess",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return material->mShininess;
        }, _1, _2)));

        // Specular
        instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Specular",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(material->mSpecularColor);
        }, _1, _2)));
    }

    // Light
    {
        instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("AmbientColor",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector3f(params->mAmbientColor);
        }, _1, _2)));

        instance->SetShaderUniform(0, ShareAutomatic<bool>("TextureEnabled",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return params->mTextureEnabled;
        }, _1, _2)));
    }

    // Line
    {
        instance->SetShaderUniform(0, ShareAutomatic<Vector4f>("Line.Color",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return Vector4f(params->mLineColor);
        }, _1, _2)));

        instance->SetShaderUniform(0, ShareAutomatic<float>("Line.Width",
                                   std::bind([ = ](const Visual *, const Camera *)
        {
            return params->mLineWidth;
        }, _1, _2)));
    }
}

}
