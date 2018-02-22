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
                               "Content/Shader/Phong.vert.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                               "Content/Shader/Phong.vert.glsl");
#endif
        shader->PushShaderFile(ShaderType::FragmentShader,
#if defined(FALCON_ENGINE_API_DIRECT3D)
                               "Content/Shader/Phong.frag.hlsl.bin");
#elif defined(FALCON_ENGINE_API_OPENGL)
                               "Content/Shader/Phong.frag.glsl");
#endif

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
    // NEW(Wuxiang): Implement spot lights?

    using namespace placeholders;

    // Transform
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::PhongTrasnformBufferData, "TransformBuffer", = )
    {
        data->mModelViewProjectionTransform = camera->GetViewProjection() * visual->mWorldTransform;
        data->mModelViewTransform = camera->GetView() * visual->mWorldTransform;

        auto normalTransform = Matrix3f(
                                   Matrix4f::Transpose(
                                       Matrix4f::Inverse(camera->GetView() * visual->mWorldTransform)));
        data->mNormalTransform0 = normalTransform[0];
        data->mNormalTransform1 = normalTransform[1];
        data->mNormalTransform2 = normalTransform[2];
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(GetShaderMask(ShaderType::VertexShader));

    // Material
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::PhongMaterialBufferData, "MaterialBuffer", = )
    {
        FALCON_ENGINE_UNUSE(camera);
        FALCON_ENGINE_UNUSE(visual);

        data->mMaterialColor.mAmbient = Vector3f(material->mAmbientColor);
        data->mMaterialTexture.mAmbientExist = material->mAmbientTexture != nullptr;
        data->mMaterialColor.mDiffuse = Vector3f(material->mDiffuseColor);
        data->mMaterialTexture.mDiffuseExist = material->mDiffuseTexture != nullptr;
        data->mMaterialColor.mEmissive = Vector3f(material->mEmissiveColor);
        data->mMaterialTexture.mEmissiveExist = material->mEmissiveTexture != nullptr;
        data->mMaterialColor.mShininess = material->mShininess;
        data->mMaterialTexture.ShininessExist = material->mShininessTexture != nullptr;
        data->mMaterialColor.mSpecular = Vector3f(material->mSpecularColor);
        data->mMaterialTexture.mSpecularExist = material->mSpecularTexture != nullptr;
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(GetShaderMask(ShaderType::FragmentShader));

    // Texture
    if (material->mAmbientTexture != nullptr)
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Ambient),
                                   material->mAmbientTexture.get(),
                                   TextureMode::Texture,
                                   ShaderType::FragmentShader);

        if (material->mAmbientSampler != nullptr)
        {
            instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Ambient),
                                       material->mAmbientSampler.get(),
                                       ShaderType::FragmentShader);
        }
    }

    if (material->mDiffuseTexture != nullptr)
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Diffuse),
                                   material->mDiffuseTexture.get(), TextureMode::Texture,
                                   ShaderType::FragmentShader);

        if (material->mDiffuseSampler != nullptr)
        {
            instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Diffuse),
                                       material->mDiffuseSampler.get(),
                                       ShaderType::FragmentShader);
        }
    }

    if (material->mEmissiveTexture != nullptr)
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Emissive),
                                   material->mEmissiveTexture.get(), TextureMode::Texture,
                                   ShaderType::FragmentShader);

        if (material->mEmissiveSampler != nullptr)
        {
            instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Emissive),
                                       material->mEmissiveSampler.get(),
                                       ShaderType::FragmentShader);
        }
    }

    if (material->mShininessTexture != nullptr)
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Shininess),
                                   material->mShininessTexture.get(), TextureMode::Texture,
                                   ShaderType::FragmentShader);

        if (material->mShininessSampler != nullptr)
        {
            instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Shininess),
                                       material->mShininessSampler.get(),
                                       ShaderType::FragmentShader);
        }
    }

    if (material->mSpecularTexture != nullptr)
    {
        instance->SetShaderTexture(0, GetTextureUnit(TextureUnit::Specular),
                                   material->mSpecularTexture.get(), TextureMode::Texture,
                                   ShaderType::FragmentShader);

        if (material->mSpecularSampler != nullptr)
        {
            instance->SetShaderSampler(0, GetTextureUnit(TextureUnit::Specular),
                                       material->mSpecularSampler.get(),
                                       ShaderType::FragmentShader);
        }
    }

    // Light
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_BEGIN(instance, 0, Detail::PhongLightBufferData, "LightBuffer", = )
    {
        FALCON_ENGINE_UNUSE(visual);

        // Directional light
        data->mDirectionalLight.mAmbient = params->mDirectionalLight == nullptr
                                           ? Vector3f::Zero
                                           : Vector3f(params->mDirectionalLight->mAmbient);
        data->mDirectionalLight.mDiffuse = params->mDirectionalLight == nullptr
                                           ? Vector3f::Zero
                                           : Vector3f(params->mDirectionalLight->mDiffuse);
        data->mDirectionalLight.mSpecular = params->mDirectionalLight == nullptr
                                            ? Vector3f::Zero
                                            : Vector3f(params->mDirectionalLight->mSpecular);
        data->mDirectionalLight.mEyeDirection = params->mDirectionalLight == nullptr
                                                ? Vector3f::Zero
                                                : Vector3f(camera->GetView() * Vector4f(params->mDirectionalLight->mDirection, 0));

        // Point light
        auto pointLightNum = int(params->mPointLightList.size());
        data->mPointLightNum = pointLightNum;
        for (int pointLightIndex = 0; pointLightIndex < PointLightNumMax; ++pointLightIndex)
        {
            if (pointLightIndex < pointLightNum)
            {
                data->mPointLightArray[pointLightIndex].mAmbient = params->mPointLightList[pointLightIndex]->mAmbient;
                data->mPointLightArray[pointLightIndex].mDiffuse = params->mPointLightList[pointLightIndex]->mDiffuse;
                data->mPointLightArray[pointLightIndex].mSpecular = params->mPointLightList[pointLightIndex]->mSpecular;
                data->mPointLightArray[pointLightIndex].mEyePosition = Vector3f(camera->GetView() * Vector4f(params->mPointLightList[pointLightIndex]->mPosition, 1));
                data->mPointLightArray[pointLightIndex].mConstant = params->mPointLightList[pointLightIndex]->mConstant;
                data->mPointLightArray[pointLightIndex].mLinear = params->mPointLightList[pointLightIndex]->mLinear;
                data->mPointLightArray[pointLightIndex].mQuadratic = params->mPointLightList[pointLightIndex]->mQuadratic;
            }
            else
            {
                data->mPointLightArray[pointLightIndex].mAmbient = Vector3f::Zero;
                data->mPointLightArray[pointLightIndex].mDiffuse = Vector3f::Zero;
                data->mPointLightArray[pointLightIndex].mSpecular = Vector3f::Zero;
                data->mPointLightArray[pointLightIndex].mEyePosition = Vector3f::Zero;
                data->mPointLightArray[pointLightIndex].mConstant = 0.0f;
                data->mPointLightArray[pointLightIndex].mLinear = 0.0f;
                data->mPointLightArray[pointLightIndex].mQuadratic = 0.0f;
            }
        }
    }
    FALCON_ENGINE_UNIFORM_BUFFER_1_SET_END(GetShaderMask(ShaderType::FragmentShader));
}

}
