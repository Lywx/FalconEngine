#include <FalconEngine/Graphics/Effect/PhongShadingEffect.h>

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
#include "FalconEngine/Graphics/Renderer/Resource/VertexGroup.h"

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PhongShadingEffect, VisualEffect);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
int PhongShadingEffect::PointLightNumMax = 6;
int PhongShadingEffect::SpotLightNumMax = 6;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongShadingEffect::PhongShadingEffect()
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/PhongShading.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/PhongShading.frag.glsl");

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

PhongShadingEffect::~PhongShadingEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PhongShadingEffect::CreateInstance(_IN_     std::shared_ptr<VisualEffect> visualEffect,
                                   _IN_OUT_ Node                         *node,
                                   _IN_     const Light&                  directionalLight,
                                   _IN_     const vector<const Light *>&  pointLightList,
                                   _IN_     const vector<const Light *>&  spotLightList)
{
    using namespace placeholders;

    CheckEffectSame(visualEffect.get());

    auto visualCreateVisualEffecetInstance = std::bind([visualEffect, &directionalLight, &pointLightList, &spotLightList, this](Visual * visual)
    {
        auto visualEffectInstance = make_shared<VisualEffectInstance>(visualEffect);
        CreateInstance(visualEffectInstance, visual, directionalLight, pointLightList, spotLightList);
    }, _1);

    TraverseVisualLevelOrder(node, visualCreateVisualEffecetInstance);
}

void
PhongShadingEffect::CreateInstance(_IN_OUT_ VisualEffectInstance        *visualEffectInstance,
                                   _IN_     const Material&              material,
                                   _IN_     const Light&                 directionalLight,
                                   _IN_     const vector<const Light *>& pointLightList,
                                   _IN_     const vector<const Light *>& /* spotLightList */) const
{
    using namespace placeholders;

    CheckEffectCompatible(visualEffectInstance);

    // Transform
    visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("ModelViewProjectionTransform",
                                           std::bind([](const Visual * visual, const Camera * camera)
    {
        // TODO(Wuxiang): Optimize this by merging projection and view transform into Dirty Flag pattern.
        return camera->GetProjection() * camera->GetView()  * visual->mWorldTransform;
    }, _1, _2)));

    visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Matrix4f>("ModelViewTransform",
                                           std::bind([](const Visual * visual, const Camera * camera)
    {
        return camera->GetView() * visual->mWorldTransform;
    }, _1, _2)));

    visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Matrix3f>("NormalTransform",
                                           std::bind([](const Visual * visual, const Camera * camera)
    {
        auto normalTransform = Matrix4f::Transpose(Matrix4f::Inverse(camera->GetView() * visual->mWorldTransform));
        return Matrix3f(normalTransform);
    }, _1, _2)));

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

    // Point light
    {
        visualEffectInstance->SetShaderUniform(0, ShareAutomatic<int>("PointLightNum",
                                               std::bind([&pointLightList](const Visual *, const Camera *)
        {
            return int(pointLightList.size());
        }, _1, _2)));

        for (int i = 0; i < PointLightNumMax; ++i)
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Ambient",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mAmbient);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Diffuse",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mDiffuse);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Specular",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(pointLight->mSpecular);
                }

                return Vector3f::Zero;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].EyePosition",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera * camera)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return Vector3f(camera->GetView() * Vector4f(pointLight->mPosition, 1));
                }

                return Vector3f::Zero;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Constant",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return pointLight->mConstant;
                }

                return 0.0f;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Linear",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
                {
                    auto *pointLight = pointLightList[i];
                    return pointLight->mLinear;
                }

                return 0.0f;
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Quadratic",
                                                   std::bind([i, &pointLightList](const Visual *, const Camera *)
            {
                if (i < int(pointLightList.size()))
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
        // TODO(Wuxiang): 2017-03-09 15:30 Add sampler.
        // Ambient
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureAmbientExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mAmbientTexture != nullptr;
            }, _1, _2)));

            // TODO(Wuxiang): Possibly add dynamic material updating?
            if (material.mAmbientTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient), material.mAmbientTexture);
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Ambient",
                                                       std::bind([&material](const Visual *, const Camera *)
                {
                    return Vector3f(material.mAmbientColor);
                }, _1, _2)));
            }
        }

        // Diffuse
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureDiffuseExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mDiffuseTexture != nullptr;
            }, _1, _2)));

            if (material.mDiffuseTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse), material.mDiffuseTexture);
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Diffuse",
                                                       std::bind([&material](const Visual *, const Camera *)
                {
                    return Vector3f(material.mDiffuseColor);
                }, _1, _2)));
            }
        }

        // Emissive
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureEmissiveExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mEmissiveTexture != nullptr;
            }, _1, _2)));

            if (material.mEmissiveTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Emissive), material.mEmissiveTexture);
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Emissive",
                                                       std::bind([&material](const Visual *, const Camera *)
                {
                    return Vector3f(material.mEmissiveColor);
                }, _1, _2)));
            }
        }

        // Shininess
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureShininessExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mShininessTexture != nullptr;
            }, _1, _2)));

            if (material.mShininessTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Shininess), material.mShininessTexture);
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("MaterialColor.Shininess",
                                                       std::bind([&material](const Visual *, const Camera *)
                {
                    return material.mShininess;
                }, _1, _2)));
            }
        }

        // Specular
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureSpecularExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mSpecularTexture != nullptr;
            }, _1, _2)));

            if (material.mSpecularTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular), material.mSpecularTexture);
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("MaterialColor.Specular",
                                                       std::bind([&material](const Visual *, const Camera *)
                {
                    return Vector3f(material.mSpecularColor);
                }, _1, _2)));
            }
        }
    }
}

std::shared_ptr<VertexFormat>
PhongShadingEffectCreateVertexFormat()
{
    auto vertexFormat = std::make_shared<VertexFormat>();

    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);

    vertexFormat->FinishVertexAttribute();

    return vertexFormat;
}

std::shared_ptr<VertexFormat>
PhongShadingEffect::GetVertexFormat() const
{
    static auto sVertexFormat = PhongShadingEffectCreateVertexFormat();
    return sVertexFormat;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PhongShadingEffect::CreateInstance(_IN_OUT_ std::shared_ptr<VisualEffectInstance> visualEffectInstance,
                                   _IN_OUT_ Visual                       *visual,
                                   _IN_     const Light&                  directionalLight,
                                   _IN_     const vector<const Light *>&  pointLightList,
                                   _IN_     const vector<const Light *>&  spotLightList) const
{

    auto mesh = visual->GetMesh();
    auto material = mesh->GetMaterial();

    FALCON_ENGINE_CHECK_NULLPTR(material);
    CreateInstance(visualEffectInstance.get(), *material, directionalLight, pointLightList, spotLightList);
    visual->SetInstance(visualEffectInstance);

    auto vertexFormat = GetVertexFormat();
    visual->SetVertexFormat(vertexFormat);

    auto vertexBuffer = mesh->GetPrimitive()->GetVertexBuffer();
    auto vertexGroup = std::make_shared<VertexGroup>();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
    visual->SetVertexGroup(vertexGroup);
}

}
