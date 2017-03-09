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
/* Static Members                                                       */
/************************************************************************/
int PhongLightingEffect::PointLightNumMax = 10;
int PhongLightingEffect::SpotLightNumMax = 10;

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
PhongLightingEffect::CreateInstance(_IN_     VisualEffectSharedPtr        effect,
                                    _IN_OUT_ Node                        *nodeRoot,
                                    _IN_     const Light                 *directionalLight,
                                    _IN_     const vector<const Light *>& pointLightList,
                                    _IN_     const vector<const Light *>& spotLightList)
{
    using namespace placeholders;

    CheckEffectSame(effect.get());

    auto meshCreateInstance = std::bind([effect, &directionalLight, &pointLightList, &spotLightList, this](Mesh * mesh)
    {
        auto instance = make_shared<VisualEffectInstance>(effect);
        CreateInstance(instance, mesh, directionalLight, pointLightList, spotLightList);
    }, _1);

    TraverseLevelOrder(nodeRoot, meshCreateInstance);
}

void
PhongLightingEffect::CreateInstance(_IN_OUT_ VisualEffectInstance        *instance,
                                    _IN_     const Material              *material,
                                    _IN_     const Light                 *directionalLight,
                                    _IN_     const vector<const Light *>& pointLightList,
                                    _IN_     const vector<const Light *>& spotLightList) const
{
    using namespace placeholders;

    CheckEffectCompatible(instance);

    // Transform
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

    // Directional light
    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Ambient",
                               std::bind([directionalLight](const Visual * visual, const Camera * camera)
    {
        return directionalLight->mAmbient;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Diffuse",
                               std::bind([directionalLight](const Visual * visual, const Camera * camera)
    {
        return directionalLight->mDiffuse;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Specular",
                               std::bind([directionalLight](const Visual * visual, const Camera * camera)
    {
        return directionalLight->mSpecular;
    }, _1, _2)));

    instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                               std::bind([directionalLight](const Visual * visual, const Camera * camera)
    {
        return camera->GetView() * directionalLight->mDirection;
    }, _1, _2)));

    // Point light
    {
        // TODO(Wuxiang): 2017-03-09 14:31 This is wrong. If you cannot have the maximum i in the start you won't be able to increase it.
        for (int i = 0; i < PointLightNumMax; ++i)
        {
            instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Ambient",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mAmbient);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Diffuse",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mDiffuse);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Specular",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mSpecular);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].EyePosition",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    // TODO(Wuxiang): Hook lamp position and light position.
                    auto *pointLight = pointLightList[i];
                    return camera->GetView() * pointLight->mPosition;
                }

                return Vector3f::Zero;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Constant",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return pointLight->mConstant;
                }

                return 0.0f;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Linear",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return pointLight->mLinear;
                }

                return 0.0f;
            }, _1, _2)));

            instance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Quadratic",
                                       std::bind([i, &pointLightList](const Visual * visual, const Camera * camera)
            {
                if (i < pointLightList.size())
                {
                    auto *pointLight = pointLightList[i];
                    return pointLight->mQuadratic;
                }

                return 0.0f;
            }, _1, _2)));
        }
    }

    // Material
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient), material->mAmbientTexture);
        instance->SetShaderTexture(0,, material->mAmbientTexture == nullptr);

        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuseTexture);
    }
    //instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuse);
    // instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular), material->mSpecular);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PhongLightingEffect::CreateInstance(_IN_OUT_ VisualEffectInstanceSharedPtr instance,
                                    _IN_OUT_ Mesh                         *mesh,
                                    _IN_     const Light                  *directionalLight,
                                    _IN_     const vector<const Light *>&  pointLightList,
                                    _IN_     const vector<const Light *>&  spotLightList) const
{
    CreateInstance(instance.get(), mesh->GetMaterial(), directionalLight, pointLightList, spotLightList);
    SetEffectInstance(mesh, instance);
}

}
