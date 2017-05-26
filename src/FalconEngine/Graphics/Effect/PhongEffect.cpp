#include <FalconEngine/Graphics/Effect/PhongEffect.h>

#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(PhongEffect);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
int PhongEffect::PointLightNumMax = 6;
int PhongEffect::SpotLightNumMax = 6;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongEffect::PhongEffect(bool initializer)
{
    if (initializer)
    {
        auto shader = std::make_shared<Shader>();
        shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Phong.vert.glsl");
        shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Phong.frag.glsl");

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

PhongEffect::~PhongEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PhongEffect::CreateInstance(Node *node, const PhongEffectParams *params) const
{
    FALCON_ENGINE_CHECK_NULLPTR(params);

    CreateInstance(node, params->mDirectionalLight, params->mPointLightList, params->mSpotLightList);
}

void
PhongEffect::CreateInstance(_IN_OUT_ Node                                      *node,
                            _IN_     const std::shared_ptr<Light>               directionalLight,
                            _IN_     const std::vector<std::shared_ptr<Light>>& pointLightList,
                            _IN_     const std::vector<std::shared_ptr<Light>>& spotLightList) const
{
    using namespace placeholders;

    VisualEffect::TraverseLevelOrder(node, std::bind([&, this](Visual * visual)
    {
        auto visualEffectInstance = CreateSetInstance(visual);

        // Set up visual effect instance.
        auto mesh = visual->GetMesh();
        InitializeInstance(visualEffectInstance.get(), mesh->GetMaterial(), directionalLight, pointLightList, spotLightList);

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
PhongEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance                      *visualEffectInstance,
                                _IN_     std::shared_ptr<Material>                  material,
                                _IN_     std::shared_ptr<Light>                     directionalLight,
                                _IN_     const std::vector<std::shared_ptr<Light>>& pointLightList,
                                _IN_     const std::vector<std::shared_ptr<Light>>& /* spotLightList */) const
{
    // TODO(Wuxiang): 2017-05-24 12:35 Implement spot lights?

    using namespace placeholders;

    // Transform
    SetShaderUniformAutomaticModelViewProjectionTransform(visualEffectInstance, 0, "ModelViewProjectionTransform");
    SetShaderUniformAutomaticModelViewTransform(visualEffectInstance, 0, "ModelViewTransform");
    SetShaderUniformAutomaticNormalTransform(visualEffectInstance, 0, "NormalTransform");

    // Material
    {
        // NOTE(Wuxiang): Assume material is not nullptr, because if it is, that
        // must be the case of the visual is being rendered is corrupted. If that
        // happens, something worse must be happening.

        // Ambient
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("fe_TextureAmbientExist",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mAmbientTexture != nullptr;
            }, _1, _2)));

            if (material->mAmbientTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient), material->mAmbientTexture);

                if (material->mAmbientSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Ambient), material->mAmbientSampler);
                }
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Ambient",
                                                       std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mAmbientColor);
                }, _1, _2)));
            }
        }

        // Diffuse
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("fe_TextureDiffuseExist",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mDiffuseTexture != nullptr;
            }, _1, _2)));

            if (material->mDiffuseTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuseTexture);

                if (material->mDiffuseSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse), material->mDiffuseSampler);
                }
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Diffuse",
                                                       std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mDiffuseColor);
                }, _1, _2)));
            }
        }

        // Emissive
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("fe_TextureEmissiveExist",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mEmissiveTexture != nullptr;
            }, _1, _2)));

            if (material->mEmissiveTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Emissive), material->mEmissiveTexture);

                if (material->mEmissiveSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Emissive), material->mEmissiveSampler);
                }
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Emissive",
                                                       std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mEmissiveColor);
                }, _1, _2)));
            }
        }

        // Shininess
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("fe_TextureShininessExist",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mShininessTexture != nullptr;
            }, _1, _2)));

            if (material->mShininessTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Shininess), material->mShininessTexture);

                if (material->mShininessSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Shininess), material->mShininessSampler);
                }
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("fe_Material.Shininess",
                                                       std::bind([ = ](const Visual *, const Camera *)
                {
                    return material->mShininess;
                }, _1, _2)));
            }
        }

        // Specular
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<bool>("fe_TextureSpecularExist",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mSpecularTexture != nullptr;
            }, _1, _2)));

            if (material->mSpecularTexture != nullptr)
            {
                visualEffectInstance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular), material->mSpecularTexture);

                if (material->mSpecularSampler != nullptr)
                {
                    visualEffectInstance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Specular), material->mSpecularSampler);
                }
            }
            else
            {
                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("fe_Material.Specular",
                                                       std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mSpecularColor);
                }, _1, _2)));
            }
        }
    }

    // Light
    {
        // Directional light
        {
            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Ambient",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                if (directionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(directionalLight->mAmbient);
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Diffuse",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                if (directionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(directionalLight->mDiffuse);
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.Specular",
                                                   std::bind([ = ](const Visual *, const Camera *)
            {
                if (directionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(directionalLight->mSpecular);
            }, _1, _2)));

            visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                                                   std::bind([ = ](const Visual *, const Camera * camera)
            {
                if (directionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(camera->GetView() * Vector4f(directionalLight->mDirection, 0));
            }, _1, _2)));

        }

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
                        return Vector3f(pointLightList[i]->mAmbient);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Diffuse",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera *)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return Vector3f(pointLightList[i]->mDiffuse);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Specular",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera *)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return Vector3f(pointLightList[i]->mSpecular);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].EyePosition",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera * camera)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return Vector3f(camera->GetView() * Vector4f(pointLightList[i]->mPosition, 1));
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Constant",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera *)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return pointLightList[i]->mConstant;
                    }

                    return 0.0f;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Linear",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera *)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return pointLightList[i]->mLinear;
                    }

                    return 0.0f;
                }, _1, _2)));

                visualEffectInstance->SetShaderUniform(0, ShareAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Quadratic",
                                                       std::bind([i, &pointLightList](const Visual *, const Camera *)
                {
                    if (i < int(pointLightList.size()))
                    {
                        return pointLightList[i]->mQuadratic;
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
PhongEffect::GetVertexFormat() const
{
    static auto sVertexFormat = PhongShadingEffectCreateVertexFormat();
    return sVertexFormat;
}

}
