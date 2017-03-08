#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>

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

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PhongLightingEffect, VisualEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongLightingEffect::PhongLightingEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/PhongLighting.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/PhongLighting.frag.glsl");

    shader->PushUniform("ModelViewProjectionTransform", ShaderUniformType::FloatMat4);
    shader->PushUniform("ModelViewTransform", ShaderUniformType::FloatMat4);
    shader->PushUniform("NormalTransform", ShaderUniformType::FloatMat3);

    shader->PushUniform("DirectionalLight.Ambient", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.Diffuse", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.Specular", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.EyeDirection", ShaderUniformType::FloatVec3);

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    blendState->mSourceFactor = BlendSourceFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendDestinationFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = true;
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

PhongLightingEffect::~PhongLightingEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PhongLightingEffect::CreateInstance(VisualEffectInstance *instance, const Light *light, const Material *material) const
{
    using namespace placeholders;

    CheckEffectCompatible(instance);

    instance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("ModelViewProjectionTransform",
                               std::bind([](const Visual * visual, const Camera * camera)
    {
        // TODO(Wuxiang): Optimize this by merging projection and view transform into Dirty Flag pattern.
        return camera->GetProjection() * camera->GetView()  * visual->mWorldTransform;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("ModelViewTransform",
                               std::bind([](const Visual * visual, const Camera * camera)
    {
        return camera->GetView() * visual->mWorldTransform;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Matrix3f>("NormalTransform",
                               std::bind([](const Visual * visual, const Camera * camera)
    {
        auto normalTransform = Matrix4f::Transpose(Matrix4f::Inverse(visual->mWorldTransform * camera->GetView()));
        return Matrix3f(normalTransform);
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Ambient",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return Vector3f(light->mAmbient);
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Diffuse",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return Vector3f(light->mDiffuse);
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Specular",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return Vector3f(light->mSpecular);
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return Vector3f(camera->GetView() * light->mDirection);
    }, _1, _2)));

    instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuse);
    //instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuse);
    // instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular), material->mSpecular);
}

void
PhongLightingEffect::CreateInstance(VisualEffectSharedPtr effect, Node *meshRoot, const Light *light)
{
    using namespace placeholders;

    CheckEffectSame(effect.get());

    auto meshCreateInstance = std::bind([effect, &light, this](Mesh * mesh)
    {
        auto instance = make_shared<VisualEffectInstance>(effect);
        CreateInstance(mesh, instance, light);
    }, _1);

    TraverseLevelOrder(meshRoot, meshCreateInstance);
}

void
PhongLightingEffect::CreateInstance(
    _IN_OUT_ Mesh                         *mesh,
    _IN_OUT_ VisualEffectInstanceSharedPtr instance,
    _IN_     const Light                  *light) const
{
    CreateInstance(instance.get(), light, mesh->GetMaterial());
    SetEffectInstance(mesh, instance);
}

}
