#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/States/BlendState.h>
#include <FalconEngine/Graphics/Renderer/States/CullState.h>
#include <FalconEngine/Graphics/Renderer/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/States/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Scene/Light.h>
#include <FalconEngine/Graphics/Scene/Material.h>

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

    shader->PushUniform("MVPTransform", ShaderUniformType::FloatMat4);
    shader->PushUniform("MVTransform", ShaderUniformType::FloatMat4);
    shader->PushUniform("NormalTransform", ShaderUniformType::FloatMat3);

    shader->PushUniform("DirectionalLight.Ambient", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.Diffuse", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.Specular", ShaderUniformType::FloatVec3);
    shader->PushUniform("DirectionalLight.EyeDirection", ShaderUniformType::FloatVec3);


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

    instance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("MVPTransform",
                               std::bind([](const Visual * visual, const Camera * camera)
    {
        // TODO(Wuxiang): Optimize this by merging projection and view transform into Dirty Flag pattern.
        return camera->GetProjection() * camera->GetView()  * visual->mWorldTransform;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("MVTransform",
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
        return light->mAmbient;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Diffuse",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return light->mDiffuse;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Specular",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return light->mSpecular;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                               std::bind([light](const Visual * visual, const Camera * camera)
    {
        return camera->GetView() * light->mDirection;
    }, _1, _2)));
}

}
