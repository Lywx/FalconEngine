#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>

#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugRenderer::DebugRenderer()
{
    mDebugBufferResource = make_shared<BufferResource>();
    mDebugEffectParams = make_shared<DebugEffectParams>();
    mDebugMessageManager = make_shared<DebugRenderMessageManager>();
}

DebugRenderer::~DebugRenderer()
{
}

enum BufferChannel
{
    ChannelLine     = 0,
    ChannelTriangle = 1,
    ChannelCount
};

const int BufferChannelMap[int(DebugRenderType::Count)] =
{
    ChannelLine,
    ChannelLine,

    ChannelLine,
    ChannelLine,
    ChannelLine,
    ChannelTriangle,

    ChannelTriangle,
};

/************************************************************************/
/* Rendering API                                                        */
/************************************************************************/
void
DebugRenderer::AddAABB(const Camera *camera,
                       const Entity *entity,
                       const Color&  color,
                       float         duration,
                       bool          depthEnabled)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    AddAABB(camera, entity->GetNode(), color, duration, depthEnabled);
}

void
DebugRenderer::AddAABB(const Camera *camera,
                       const Node   *node,
                       const Color&  color,
                       float         duration,
                       bool          depthEnabled)
{
    FALCON_ENGINE_CHECK_NULLPTR(node);

    auto slotNum = node->GetChildrenSlotNum();
    for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
    {
        auto child = node->GetChildAt(slotIndex);
        if (auto childVisual = dynamic_cast<const Visual *>(child))
        {
            AddAABB(camera, childVisual, color, duration, depthEnabled);
        }
        else if (auto childNode = dynamic_cast<const Node *>(child))
        {
            AddAABB(camera, childNode, color, duration, depthEnabled);
        }
    }
}

void
DebugRenderer::AddAABB(const Camera *camera,
                       const Visual *visual,
                       const Color&  color,
                       float         duration,
                       bool          depthEnabled)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);

    auto aabb = visual->GetMesh()->GetAABB();

    AddAABB(camera,
            Vector3f(visual->mWorldTransform * Vector4f(aabb->mMin, 1)),
            Vector3f(visual->mWorldTransform * Vector4f(aabb->mMax, 1)),
            color, duration, depthEnabled);
}

void
DebugRenderer::AddAABB(const Camera   *camera,
                       const Vector3f& min,
                       const Vector3f& max,

                       const Color&    color,
                       float           duration,
                       bool            depthEnabled)
{
    mDebugMessageManager->mMessageList.emplace_back(
        camera, DebugRenderType::AABB, 0.f,
        min, max, color, duration,
        depthEnabled);
}

void
DebugRenderer::AddCamera(const Camera *camera)
{
    mDebugEffectParams->AddCamera(camera);
}

void
DebugRenderer::RemoveCamera(const Camera *camera)
{
    mDebugEffectParams->RemoveCamera(camera);
}

void
DebugRenderer::AddCircle(const Camera   *camera,
                         const Vector3f& center,
                         const Vector3f& normal,
                         float           radius,

                         const Color&    color,
                         float           duration,
                         bool            depthEnabled)
{
    mDebugMessageManager->mMessageList.emplace_back(
        camera, DebugRenderType::Circle, radius,
        center, normal, color, duration,
        depthEnabled);
}

void
DebugRenderer::AddCross(const Camera   *camera,
                        const Vector3f& center,
                        float           radius,

                        const Color&    color,
                        float           duration,
                        bool            depthEnabled)
{
    mDebugMessageManager->mMessageList.emplace_back(camera,
            DebugRenderType::Cross, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

void
DebugRenderer::AddLine(const Camera   *camera,
                       const Vector3f& from,
                       const Vector3f& to,

                       const Color&    color,
                       float           duration,
                       bool            depthEnabled)
{
    mDebugMessageManager->mMessageList.emplace_back(camera,
            DebugRenderType::Line, 0.f,
            from, to, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddSphere(const Camera   *camera,
                         const Vector3f& center,
                         float           radius,

                         const Color&    color,
                         float           duration,
                         bool            depthEnabled)
{
    mDebugMessageManager->mMessageList.emplace_back(camera,
            DebugRenderType::Sphere, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

/************************************************************************/
/* Rendering Engine API                                                 */
/************************************************************************/
void
DebugRenderer::Initialize()
{
    const auto LineMaxNum = int(Kilobytes(100));
    const auto TriangleMaxNum = int(Kilobytes(100));

    auto noDepthEffect = make_shared<DebugEffect>(false);
    auto hasDepthEffect = make_shared<DebugEffect>(true);

    CreateChannel<PrimitiveLines>(
        ChannelLine,
        LineMaxNum * 2, noDepthEffect);
    CreateChannel<PrimitiveLines>(
        ChannelLine + ChannelCount,
        LineMaxNum * 2, hasDepthEffect);

    CreateChannel<PrimitiveTriangles>(
        ChannelTriangle,
        TriangleMaxNum * 3, noDepthEffect);
    CreateChannel<PrimitiveTriangles>(
        ChannelTriangle + ChannelCount,
        TriangleMaxNum * 3, hasDepthEffect);
}

void
DebugRenderer::RenderBegin()
{
    mDebugBufferResource->Reset();
}

void
DebugRenderer::Render(double /* percent */)
{
    mDebugBufferResource->Draw(nullptr);
}

void
DebugRenderer::RenderEnd()
{
}

void
DebugRenderer::UpdateFrame(double elapsed)
{
    // Compute channel size.
    for (auto& message : mDebugMessageManager->mMessageList)
    {
        // Find channel index.
        int channel = BufferChannelMap[int(message.mType)];
        channel = message.mDepthEnabled
                  ? channel + ChannelCount
                  : channel;

        // Update channel data number.
        switch (message.mType)
        {
        case DebugRenderType::AABB:
            mDebugBufferResource->UpdateChannelElement(channel, 24);
            break;
        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case DebugRenderType::Circle:
            mDebugBufferResource->UpdateChannelElement(
                channel, DebugRendererHelper::CircleSampleNum * 2);
            break;
        case DebugRenderType::Cross:
            mDebugBufferResource->UpdateChannelElement(
                channel, 6);
            break;
        case DebugRenderType::Line:
            mDebugBufferResource->UpdateChannelElement(
                channel, 2);
            break;
        case DebugRenderType::Sphere:
            mDebugBufferResource->UpdateChannelElement(
                channel, DebugRendererHelper::SpherePhiSampleNum
                * DebugRendererHelper::SphereThetaSampleNum * 6);
            break;
        case DebugRenderType::Text:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    mDebugBufferResource->FillBegin(
        BufferAccessMode::WriteBuffer,
        BufferFlushMode::Automatic,
        BufferSynchronizationMode::Unsynchronized);

    {
        // Fill channel buffer data.
        for (auto& message : mDebugMessageManager->mMessageList)
        {
            // Find channel index.
            int channel = BufferChannelMap[int(message.mType)];
            channel = message.mDepthEnabled
                      ? channel + ChannelCount
                      : channel;

            // Get buffer data pointer.
            BufferAdaptor *bufferAdaptor;
            unsigned char *bufferData;
            std::tie(bufferAdaptor, bufferData) = mDebugBufferResource->GetChannelData(channel);

            int cameraIndex = mDebugEffectParams->mCameraSlotTable[message.mCamera];

            // Fill vertex data by inspecting the message.
            switch (message.mType)
            {
            case DebugRenderType::AABB:
                DebugRendererHelper::FillAABB(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloatVector2, message.mColor, cameraIndex);
                break;
            case DebugRenderType::OBB:
                FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            case DebugRenderType::Circle:
                DebugRendererHelper::FillCircle(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloatVector2, message.mFloat1, message.mColor,
                    cameraIndex);
                break;
            case DebugRenderType::Cross:
                DebugRendererHelper::FillCross(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloat1, message.mColor, cameraIndex);
                break;
            case DebugRenderType::Line:
                DebugRendererHelper::FillLine(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloatVector2, message.mColor, cameraIndex);
                break;
            case DebugRenderType::Sphere:
                DebugRendererHelper::FillSphere(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloat1, message.mColor, cameraIndex);
                break;
            case DebugRenderType::Text:
                FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            default:
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
        }
    }

    mDebugBufferResource->FillEnd();

    // Remove time-out message.
    mDebugMessageManager->UpdateFrame(elapsed);

    // Update transform uniform.
    for (auto cameraIndexPair : mDebugEffectParams->mCameraSlotTable)
    {
        int cameraIndex = cameraIndexPair.second;
        auto camera = cameraIndexPair.first;

        mDebugEffectParams->mCameraSlotUniform[cameraIndex]->SetValue(
            camera->GetViewProjection());
    }
}

}
