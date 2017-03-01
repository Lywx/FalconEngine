#include <FalconEngine/Graphics/Effects/PhongLightingEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
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

    // TODO(Wuxiang 2017-01-22 10:41): Fix this with a default shader storage.
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/PhongLighting.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/PhongLighting.frag.glsl");

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
    pass->SetOffsetState(make_unique<OffsetState>());
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
void
PhongLightingEffect::CreateInstance(VisualEffectInstance *instance, const Light *light, const Material *material) const
{
    CheckEffectCompatible(instance);

    // TODO(Wuxiang 2017-01-23 10:46): Try to implement this.
    instance->SetShaderUniform(0, ShareConstant<Vector4f>("", light->mAmbient));
    instance->SetShaderUniform(0, ShareConstant<Vector4f>("", light->mDiffuse));
    instance->SetShaderUniform(0, ShareConstant<Vector4f>("", light->mSpecular));

    //instance->SetVertexConstant(0, 0, new0 PVWMatrixConstant());
    //instance->SetVertexConstant(0, 1, new0 MaterialEmissiveConstant(material));
    //instance->SetVertexConstant(0, 2,
    //                            new0 MaterialAmbientConstant(material));
    //instance->SetVertexConstant(0, 3,
    //                            new0 LightAmbientConstant(light));
    //instance->SetVertexConstant(0, 4,
    //                            new0 LightAttenuationConstant(light));
}

}
