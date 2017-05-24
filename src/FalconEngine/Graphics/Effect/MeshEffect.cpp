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
MeshEffect::CreateInstance(_IN_ Node        *node,
                           _IN_ Color        ambient,
                           _IN_ const Light& directionalLight,
                           _IN_ Color        lineColor,
                           _IN_ float        lineWidth) const
{
    using namespace placeholders;

    VisualEffect::TraverseLevelOrder(node, std::bind([ambient, &directionalLight, lineColor, lineWidth, this](Visual * visual)
    {
        auto visualEffectInstance = CreateSetInstance(visual);

        // Set up visual effect instance.
        auto mesh = visual->GetMesh();
        auto material = mesh->GetMaterial();
        FALCON_ENGINE_CHECK_NULLPTR(material);
        InitializeInstance(visualEffectInstance.get(), ambient, *material, directionalLight, lineColor, lineWidth);

        // Set up visual.
        auto vertexFormat = GetVertexFormat();
        visual->SetVertexFormat(vertexFormat);
        auto vertexBuffer = mesh->GetPrimitive()->GetVertexBuffer();
        auto vertexGroup = std::make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
        visual->SetVertexGroup(vertexGroup);
    }, _1));
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
MeshEffectCreateVertexFormat()
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
    static auto sVertexFormat = MeshEffectCreateVertexFormat();
    return sVertexFormat;
}

void
MeshEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance *visualEffectInstance,
                               _IN_     Color                 ambient,
                               _IN_     const Material&       material,
                               _IN_     const Light&          directionalLight,
                               _IN_     Color                 lineColor,
                               _IN_     float                 lineWidth) const
{
    using namespace placeholders;

    // Transform
    SetShaderUniformAutomaticModelViewProjectionTransform(visualEffectInstance, 0, "ModelViewProjectionTransform");
    SetShaderUniformAutomaticModelViewTransform(visualEffectInstance, 0, "ModelViewTransform");
    SetShaderUniformAutomaticNormalTransform(visualEffectInstance, 0, "NormalTransform");
    SetShaderUniformAutomaticScreenTransform(visualEffectInstance, 0, "ScreenTransform");

    // Material
    {
        // Ambient
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Ambient",
                                               std::bind([&material](const Visual *, const Camera *)
        {
            return Vector3f(material.mAmbientColor);
        }, _1, _2)));

        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("AmbientOffset",
                                               std::bind([ambient](const Visual *, const Camera *)
        {
            return Vector3f(ambient);
        }, _1, _2)));

        // Diffuse
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Diffuse",
                                               std::bind([&material](const Visual *, const Camera *)
        {
            return Vector3f(material.mDiffuseColor);
        }, _1, _2)));

        // Emissive
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Emissive",
                                               std::bind([&material](const Visual *, const Camera *)
        {
            return Vector3f(material.mEmissiveColor);
        }, _1, _2)));

        // Shininess
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("MaterialColor.Shininess",
                                               std::bind([&material](const Visual *, const Camera *)
        {
            return material.mShininess;
        }, _1, _2)));

        // Specular
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Specular",
                                               std::bind([&material](const Visual *, const Camera *)
        {
            return Vector3f(material.mSpecularColor);
        }, _1, _2)));
    }

    // Light
    {
        // Directional light
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Ambient",
                                               std::bind([&directionalLight](const Visual *, const Camera *)
        {
            return Vector3f(directionalLight.mAmbient);
        }, _1, _2)));

        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Diffuse",
                                               std::bind([&directionalLight](const Visual *, const Camera *)
        {
            return Vector3f(directionalLight.mDiffuse);
        }, _1, _2)));

        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Specular",
                                               std::bind([&directionalLight](const Visual *, const Camera *)
        {
            return Vector3f(directionalLight.mSpecular);
        }, _1, _2)));

        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                                               std::bind([&directionalLight](const Visual *, const Camera * camera)
        {
            return Vector3f(camera->GetView() * Vector4f(directionalLight.mDirection, 0));
        }, _1, _2)));
    }

    // Line
    {
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector4f>("Line.Color",
                                               std::bind([lineColor](const Visual *, const Camera *)
        {
            return Vector4f(lineColor);
        }, _1, _2)));

        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("Line.Width",
                                               std::bind([lineWidth](const Visual *, const Camera *)
        {
            return lineWidth;
        }, _1, _2)));
    }
}

}
