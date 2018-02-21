#include <FalconEngine/Graphics/Effect/PhongEffect.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(PhongEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongEffect::PhongEffect(bool initializer)
{
    if (initializer)
    {
        auto shader = std::make_shared<Shader>();
        shader->PushShaderFile(ShaderType::VertexShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                               "Content/Shader/Phong.vert.hlsl");
#elif defined(FALCON_ENGINE_API_OPENGL)
                               "Content/Shader/Phong.vert.glsl");
#endif
        shader->PushShaderFile(ShaderType::FragmentShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                               "Content/Shader/Phong.frag.hlsl");
#elif defined(FALCON_ENGINE_API_OPENGL)
                               "Content/Shader/Phong.frag.glsl");
#endif

        auto pass = make_unique<VisualEffectPass>();
        pass->SetShader(shader);

        auto shaderVertexFormat = std::make_shared<VertexFormat>();
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
}

PhongEffect::~PhongEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PhongEffect::CreateInstance(
    _IN_OUT_ Node                                     *node,
    _IN_     const std::shared_ptr<PhongEffectParams>& params)
{
    FALCON_ENGINE_CHECK_NULLPTR(params);

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
PhongEffect::InitializeInstance(_IN_OUT_ VisualEffectInstance                     *instance,
                                _IN_     const std::shared_ptr<Material>&          material,
                                _IN_     const std::shared_ptr<PhongEffectParams>& params) const
{
    // NEW(Wuxiang): 2017-05-24 12:35 Implement spot lights?

    using namespace placeholders;

    // Transform
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::PhongTrasnformBufferData, "TransformBuffer", = )
    {
        data->mModelViewProjectionTransform = camera->GetViewProjection() * visual->mWorldTransform;
        data->mModelViewTransform = camera->GetView() * visual->mWorldTransform;

        auto normalTransform = Matrix4f::Transpose(Matrix4f::Inverse(camera->GetView() * visual->mWorldTransform));
        data->mNormalTransform = Matrix3f(normalTransform);
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(GetShaderMask(ShaderType::VertexShader));

    // Material
    {
        // NOTE(Wuxiang): Assume material is not nullptr, because if it is, that
        // must be the case of the visual is being rendered is corrupted. If that
        // happens, something worse must be happening.

        // Ambient
        {
            instance->SetUniform(0, ShareUniformAutomatic<bool>("fe_TextureAmbientExist",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mAmbientTexture != nullptr;
            }, _1, _2)));

            if (material->mAmbientTexture != nullptr)
            {
                instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient),
                                           material->mAmbientTexture,
                                           TextureMode::Texture,
                                           ShaderType::FragmentShader);

                if (material->mAmbientSampler != nullptr)
                {
                    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Ambient),
                                               material->mAmbientSampler,
                                               ShaderType::FragmentShader);
                }
            }
            else
            {
                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Ambient",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mAmbientColor);
                }, _1, _2)));
            }
        }

        // Diffuse
        {
            instance->SetUniform(0, ShareUniformAutomatic<bool>("fe_TextureDiffuseExist",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mDiffuseTexture != nullptr;
            }, _1, _2)));

            if (material->mDiffuseTexture != nullptr)
            {
                instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse),
                                           material->mDiffuseTexture, TextureMode::Texture,
                                           ShaderType::FragmentShader);

                if (material->mDiffuseSampler != nullptr)
                {
                    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse),
                                               material->mDiffuseSampler,
                                               ShaderType::FragmentShader);
                }
            }
            else
            {
                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Diffuse",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mDiffuseColor);
                }, _1, _2)));
            }
        }

        // Emissive
        {
            instance->SetUniform(0, ShareUniformAutomatic<bool>("fe_TextureEmissiveExist",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mEmissiveTexture != nullptr;
            }, _1, _2)));

            if (material->mEmissiveTexture != nullptr)
            {
                instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Emissive),
                                           material->mEmissiveTexture, TextureMode::Texture,
                                           ShaderType::FragmentShader);

                if (material->mEmissiveSampler != nullptr)
                {
                    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Emissive),
                                               material->mEmissiveSampler,
                                               ShaderType::FragmentShader);
                }
            }
            else
            {
                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Emissive",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    return Vector3f(material->mEmissiveColor);
                }, _1, _2)));
            }
        }

        // Shininess
        {
            instance->SetUniform(0, ShareUniformAutomatic<bool>("fe_TextureShininessExist",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mShininessTexture != nullptr;
            }, _1, _2)));

            if (material->mShininessTexture != nullptr)
            {
                instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Shininess),
                                           material->mShininessTexture, TextureMode::Image,
                                           ShaderType::FragmentShader);

                if (material->mShininessSampler != nullptr)
                {
                    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Shininess),
                                               material->mShininessSampler,
                                               ShaderType::FragmentShader);
                }
            }
            else
            {
                instance->SetUniform(0, ShareUniformAutomatic<float>("fe_Material.Shininess",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    return material->mShininess;
                }, _1, _2)));
            }
        }

        // Specular
        {
            instance->SetUniform(0, ShareUniformAutomatic<bool>("fe_TextureSpecularExist",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return material->mSpecularTexture != nullptr;
            }, _1, _2)));

            if (material->mSpecularTexture != nullptr)
            {
                instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular),
                                           material->mSpecularTexture, TextureMode::Image,
                                           ShaderType::FragmentShader);

                if (material->mSpecularSampler != nullptr)
                {
                    instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Specular),
                                               material->mSpecularSampler,
                                               ShaderType::FragmentShader);
                }
            }
            else
            {
                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("fe_Material.Specular",
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
            instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("DirectionalLight.Ambient",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                if (params->mDirectionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(params->mDirectionalLight->mAmbient);
            }, _1, _2)));

            instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("DirectionalLight.Diffuse",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                if (params->mDirectionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(params->mDirectionalLight->mDiffuse);
            }, _1, _2)));

            instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("DirectionalLight.Specular",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                if (params->mDirectionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(params->mDirectionalLight->mSpecular);
            }, _1, _2)));

            instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("DirectionalLight.EyeDirection",
                                 std::bind([ = ](const Visual *, const Camera * camera)
            {
                if (params->mDirectionalLight == nullptr)
                {
                    return Vector3f::Zero;
                }

                return Vector3f(camera->GetView() * Vector4f(params->mDirectionalLight->mDirection, 0));
            }, _1, _2)));

        }

        // Point light
        {
            instance->SetUniform(0, ShareUniformAutomatic<int>("PointLightNum",
                                 std::bind([ = ](const Visual *, const Camera *)
            {
                return int(params->mPointLightList.size());
            }, _1, _2)));

            for (int i = 0; i < PointLightNumMax; ++i)
            {
                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Ambient",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return Vector3f(params->mPointLightList[i]->mAmbient);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Diffuse",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return Vector3f(params->mPointLightList[i]->mDiffuse);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].Specular",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return Vector3f(params->mPointLightList[i]->mSpecular);
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<Vector3f>("PointLightArray[" + std::to_string(i) + "].EyePosition",
                                     std::bind([ = ](const Visual *, const Camera * camera)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return Vector3f(camera->GetView() * Vector4f(params->mPointLightList[i]->mPosition, 1));
                    }

                    return Vector3f::Zero;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Constant",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return params->mPointLightList[i]->mConstant;
                    }

                    return 0.0f;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Linear",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return params->mPointLightList[i]->mLinear;
                    }

                    return 0.0f;
                }, _1, _2)));

                instance->SetUniform(0, ShareUniformAutomatic<float>("PointLightArray[" + std::to_string(i) + "].Quadratic",
                                     std::bind([ = ](const Visual *, const Camera *)
                {
                    if (i < int(params->mPointLightList.size()))
                    {
                        return params->mPointLightList[i]->mQuadratic;
                    }

                    return 0.0f;
                }, _1, _2)));
            }
        }
    }
}

}
