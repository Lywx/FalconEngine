#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PhongLightingEffect, VisualEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PhongLightingEffect::PhongLightingEffect()
{
    auto shader = make_shared<Shader>();

    // TODO(Wuxiang 2017-01-22 10:41): Fix this with a default shader storage.
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/PhongLighting.vert.glsl");
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/PhongLighting.frag.glsl");

    shader->PushAttribute(0, "modelPosition", ShaderVertexAttributeType::FloatVec3, false);
    shader->PushUniform("PVWMatrix", ShaderUniformType::FloatMat4);

    // TODO(Wuxiang 2017-01-22 11:09): Fix this later.
    //shader->SetConstant(1, "MaterialEmissive", 1);
    //shader->SetConstant(2, "MaterialAmbient", 1);
    //shader->SetConstant(3, "LightAmbient", 1);
    //shader->SetConstant(4, "LightAttenuation", 1);

    auto pass = make_unique<VisualPass>();
    pass->SetShader(shader);
    pass->SetBlendState(make_unique<BlendState>());
    pass->SetCullState(make_unique<CullState>());
    pass->SetDepthTestState(make_unique<DepthTestState>());
    pass->SetOffsetState(make_unique< OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());
    pass->SetWireframeState(make_unique<WireframeState>());
    InsertPass(move(pass));
}

PhongLightingEffect::~PhongLightingEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
VisualEffectInstance *
PhongLightingEffect::CreateInstance(VisualEffectInstance *instance, const Light *light, const Material *material) const
{
    if (!instance->GetEffect()->GetType().IsExactly(GetType()))
    {
        FALCON_ENGINE_NOT_SUPPORT();
    }

    // TODO(Wuxiang 2017-01-23 10:46): Try to implement this.
    instance->SetShaderUniform(0, new ShaderUniformConstant<Vector4f>("", light->mAmbient));
    instance->SetShaderUniform(0, new ShaderUniformConstant<Vector4f>("", light->mDiffuse));
    instance->SetShaderUniform(0, new ShaderUniformConstant<Vector4f>("", light->mSpecular));

    //instance->SetVertexConstant(0, 0, new0 PVWMatrixConstant());
    //instance->SetVertexConstant(0, 1, new0 MaterialEmissiveConstant(material));
    //instance->SetVertexConstant(0, 2,
    //                            new0 MaterialAmbientConstant(material));
    //instance->SetVertexConstant(0, 3,
    //                            new0 LightAmbientConstant(light));
    //instance->SetVertexConstant(0, 4,
    //                            new0 LightAttenuationConstant(light));
    return instance;
}

VisualEffectInstance *
PhongLightingEffect::CreateInstance(const Light *light, const Material *material)
{
    auto instance = new VisualEffectInstance(GetSharedPtr());
    return CreateInstance(instance, light, material);
}

}
