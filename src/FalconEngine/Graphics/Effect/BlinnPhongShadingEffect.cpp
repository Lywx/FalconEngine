#include <FalconEngine/Graphics/Effect/BlinnPhongShadingEffect.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_EFFECT_IMPLEMENT(BlinnPhongShadingEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BlinnPhongShadingEffect::BlinnPhongShadingEffect(bool initializer) :
    PhongShadingEffect(false)
{
    if (initializer)
    {
        auto shader = std::make_shared<Shader>();
        shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/BlinnPhongShading.vert.glsl");
        shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/BlinnPhongShading.frag.glsl");

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

BlinnPhongShadingEffect::~BlinnPhongShadingEffect()
{
}

}
