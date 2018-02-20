#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformManual.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffectParams::DebugEffectParams()
{
    // Set camera projection parameter for each taken camera slot.
    for (int cameraIndex = 0; cameraIndex < DebugEffect::CameraNumMax; ++cameraIndex)
    {
        auto cameraUniform = ShareUniformManual<Matrix4f>(
                                 string("ViewProjectionTransformArray[")
                                 + std::to_string(cameraIndex) + "]",
                                 Matrix4f::Identity);

        mCameraSlotUniform.push_back(cameraUniform);
    }
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
DebugEffectParams::AddCamera(const Camera *camera)
{
    if (mCameraSlotTable.find(camera) == mCameraSlotTable.end())
    {
        int cameraIndex;

        auto cameraIndexIter = find(mCameraSlot.begin(),
                                    mCameraSlot.end(),
                                    false);

        if (cameraIndexIter == mCameraSlot.end())
        {
            mCameraSlot.push_back(true);
            cameraIndex = int(mCameraSlot.size()) - 1;
        }
        else
        {
            cameraIndex = int(cameraIndexIter - mCameraSlot.begin());
        }

        int cameraNum = int(mCameraSlotTable.size());
        if (cameraNum < DebugEffect::CameraNumMax)
        {
            mCameraSlotTable.insert({camera, cameraIndex});
        }
        else
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Don't support camera number "
                                                  "more than the defined constant.");
        }
    }
}

void
DebugEffectParams::RemoveCamera(const Camera *camera)
{
    auto cameraIter = mCameraSlotTable.find(camera);
    if (cameraIter != mCameraSlotTable.end())
    {
        auto cameraIndex = cameraIter->second;
        mCameraSlot[cameraIndex] = false;
        mCameraSlotTable.erase(cameraIter);
    }
}

FALCON_ENGINE_EFFECT_IMPLEMENT(DebugEffect);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const int
DebugEffect::CameraNumMax = 4;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffect::DebugEffect(bool depthTestEnabled)
{
    auto shader = std::make_shared<Shader>();
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shader/Debug.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shader/Debug.frag.glsl");

    auto pass = make_unique<VisualEffectPass>();
    pass->SetShader(shader);

    auto shaderVertexFormat = std::make_shared<VertexFormat>();
    shaderVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    shaderVertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 0);
    shaderVertexFormat->PushVertexAttribute(2, "Camera", VertexAttributeType::Int, false, 0);
    shaderVertexFormat->FinishVertexAttribute();
    pass->SetShaderVertexFormat(shaderVertexFormat);

    auto blendState = make_unique<BlendState>();
    blendState->mEnabled = false;
    blendState->mSourceFactor = BlendFactor::SRC_ALPHA;
    blendState->mDestinationFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
    pass->SetBlendState(move(blendState));

    auto cullState = make_unique<CullState>();
    cullState->mEnabled = false;
    pass->SetCullState(move(cullState));

    auto depthTestState = make_unique<DepthTestState>();
    depthTestState->mEnabled = depthTestEnabled;
    pass->SetDepthTestState(move(depthTestState));

    pass->SetOffsetState(make_unique<OffsetState>());
    pass->SetStencilTestState(make_unique<StencilTestState>());

    auto wireframwState = make_unique<WireframeState>();
    wireframwState->mEnabled = true;
    pass->SetWireframeState(move(wireframwState));

    InsertPass(move(pass));
}

DebugEffect::~DebugEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
DebugEffect::CreateInstance(Visual *visual, const std::shared_ptr<DebugEffectParams>& params)
{
    auto instance = InstallInstance(visual, params);
    InitializeInstance(instance.get(), params);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
DebugEffect::InitializeInstance(
    VisualEffectInstance              *instance,
    std::shared_ptr<DebugEffectParams> params) const
{
    using namespace std;
    using namespace std::placeholders;

    for (int cameraIndex = 0; cameraIndex < CameraNumMax; ++cameraIndex)
    {
        instance->SetUniform(0, params->mCameraSlotUniform[cameraIndex]);
    }
}

}
