#include <FalconEngine/Graphics/Effect/PhongShadingEffect.h>

#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(PhongShadingEffect);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
int PhongShadingEffect::PointLightNumMax = 6;
int PhongShadingEffect::SpotLightNumMax = 6;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongShadingEffect::PhongShadingEffect(bool initializer)
{
    if (initializer)
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
}

PhongShadingEffect::~PhongShadingEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PhongShadingEffect::CreateInstance(_IN_OUT_ Node                        *node,
                                   _IN_     const Light&                 directionalLight,
                                   _IN_     const vector<const Light *>& pointLightList,
                                   _IN_     const vector<const Light *>& spotLightList) const
{
    using namespace placeholders;

    VisualEffect::TraverseLevelOrder(node, std::bind([&directionalLight, &pointLightList, &spotLightList, this](Visual * visual)
    {
        auto visualEffectInstance = CreateSetInstance(visual);

        // Set up visual effect instance.
        auto mesh = visual->GetMesh();
        auto material = mesh->GetMaterial();
        FALCON_ENGINE_CHECK_NULLPTR(material);
        InitializeInstance(visualEffectInstance.get(), *material, directionalLight, pointLightList, spotLightList);

        // Set up visual.
        auto vertexFormat = GetVertexFormat();
        visual->SetVertexFormat(vertexFormat);
        auto vertexBuffer = mesh->GetPrimitive()->GetVertexBuffer();
        auto vertexGroup = std::make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
        visual->SetVertexGroup(vertexGroup);
    }, _1));
}

void
PhongShadingEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance        *visualEffectInstance,
                                       _IN_     const Material&              material,
                                       _IN_     const Light&                 directionalLight,
                                       _IN_     const vector<const Light *>& pointLightList,
                                       _IN_     const vector<const Light *>& /* spotLightList */) const
{
    // TODO(Wuxiang): 2017-05-24 12:35 Implement spot lights?

    using namespace placeholders;

    // Transform
    SetShaderUniformAutomaticModelViewProjectionTransform(visualEffectInstance, 0, "ModelViewProjectionTransform");
    SetShaderUniformAutomaticModelViewTransform(visualEffectInstance, 0, "ModelViewTransform");
    SetShaderUniformAutomaticNormalTransform(visualEffectInstance, 0, "NormalTransform");

    // Material
    {
        // Ambient
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("TextureAmbientExist",
                                                   std::bind([&material](const Visual *, const Camera *)
            {
                return material.mAmbientTexture != nullptr;
            }, _1, _2)));

            if (material.mAmbientTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient), material.mAmbientTexture);

                if (material.mAmbientSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Ambient), material.mAmbientSampler);
                }
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

                if (material.mDiffuseSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse), material.mDiffuseSampler);
                }
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

                if (material.mEmissiveSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Emissive), material.mEmissiveSampler);
                }
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

                if (material.mShininessSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Shininess), material.mShininessSampler);
                }
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

                if (material.mSpecularSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Specular), material.mSpecularSampler);
                }
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

}
