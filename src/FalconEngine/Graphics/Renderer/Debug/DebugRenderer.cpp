#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>

#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include "FalconEngine/Graphics/Renderer/Renderer.h"

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugRenderer::DebugRenderer() :
    mVertexResource(make_shared<VertexResource>())
{
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

    Matrix4f modelViewProjectionTransform = camera->GetViewProjection()
                                            * visual->mWorldTransform;

    AddAABB(Vector3f(modelViewProjectionTransform * Vector4f(aabb->mMin, 1)),
            Vector3f(modelViewProjectionTransform * Vector4f(aabb->mMax, 1)),
            color, duration, depthEnabled);
}

void
DebugRenderer::AddAABB(const Vector3f& min,
                       const Vector3f& max,
                       const Color&    color,
                       float           duration,
                       bool            depthEnabled)
{
    mMessageManager->mMessageList.emplace_back(DebugRenderType::AABB, 0.f,
            min, max, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddCircle(const Vector3f& center, const Vector3f& normal, float radius, const Color& color, float duration, bool depthEnabled)
{
    mMessageManager->mMessageList.emplace_back(DebugRenderType::Circle, radius,
            center, normal, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddCross(const Vector3f& center, float radius, const Color& color, float duration, bool depthEnabled)
{
    mMessageManager->mMessageList.emplace_back(DebugRenderType::Cross, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

void
DebugRenderer::AddLine(const Vector3f& from, const Vector3f& to, const Color& color, float duration, bool depthEnabled)
{
    mMessageManager->mMessageList.emplace_back(DebugRenderType::Line, 0.f,
            from, to, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddSphere(const Vector3f& center, float radius, const Color& color, float duration, bool depthEnabled)
{
    mMessageManager->mMessageList.emplace_back(DebugRenderType::Sphere, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

/************************************************************************/
/* Rendering Engine API                                                 */
/************************************************************************/
void
DebugRenderer::Initialize()
{
    const auto LineMaxNum = int(Kilobytes(32));
    const auto TriangleMaxNum = int(Kilobytes(32));

    CreateChannel<PrimitiveLines>(
        ChannelLine,
        LineMaxNum * 2, make_shared<DebugEffect>(false));
    CreateChannel<PrimitiveLines>(
        ChannelLine + ChannelCount,
        LineMaxNum * 2, make_shared<DebugEffect>(true));

    CreateChannel<PrimitiveTriangles>(
        ChannelTriangle,
        TriangleMaxNum * 3, make_shared<DebugEffect>(false));
    CreateChannel<PrimitiveTriangles>(
        ChannelTriangle + ChannelCount,
        TriangleMaxNum * 3, make_shared<DebugEffect>(true));
}

void
DebugRenderer::RenderBegin()
{
    // TODO(Wuxiang): visual data update.
    int channelNum = ChannelCount * 2;
    for (int channel = 0; channel < channelNum; ++channel)
    {
        mVertexResource->ResetChannel(channel);
    }
}

void
DebugRenderer::Render(Renderer *renderer, double percent)
{
    int channelNum = ChannelCount * 2;
    for (int channel = 0; channel < channelNum; ++channel)
    {
        // TODO(Wuxiang): Bad performance?
        auto visual = mVertexResource->GetChannelVisual(channel);
        renderer->Draw(nullptr, visual);
    }
}

void
DebugRenderer::RenderEnd()
{
}

void
DebugRenderer::Update(double elapsed)
{
    // Compute channel size.
    for (auto& message : mMessageManager->mMessageList)
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
            mVertexResource->UpdateChannel(channel, 24);
            break;
        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case DebugRenderType::Circle:
            mVertexResource->UpdateChannel(
                channel, DebugRendererHelper::CircleSampleNum * 2);
            break;
        case DebugRenderType::Cross:
            mVertexResource->UpdateChannel(
                channel, 6);
            break;
        case DebugRenderType::Line:
            mVertexResource->UpdateChannel(
                channel, 2);
            break;
        case DebugRenderType::Sphere:
            mVertexResource->UpdateChannel(
                channel, DebugRendererHelper::SpherePhiSampleNum
                * DebugRendererHelper::SphereThetaSampleNum * 6);
            break;
        case DebugRenderType::Text:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    // Map channel buffers.
    mVertexResource->MapChannel(BufferAccessMode::WriteBuffer,
                                BufferFlushMode::Automatic,
                                BufferSynchronizationMode::Unsynchronized);

    // Fill channel buffer data.
    for (auto& message : mMessageManager->mMessageList)
    {
        // Find channel index.
        int channel = BufferChannelMap[int(message.mType)];
        channel = message.mDepthEnabled
                  ? channel + ChannelCount
                  : channel;

        // Get buffer data pointer.
        BufferAdaptor *bufferAdaptor;
        unsigned char *bufferData;
        std::tie(bufferAdaptor, bufferData) = mVertexResource->GetChannelData(channel);

        // Fill vertex data by inspecting the message.
        switch (message.mType)
        {
        case DebugRenderType::AABB:
            DebugRendererHelper::FillAABB(
                bufferAdaptor, bufferData, message.mFloatVector1,
                message.mFloatVector2, message.mColor);
            break;

        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;

        case DebugRenderType::Circle:
            DebugRendererHelper::FillCircle(
                bufferAdaptor, bufferData, message.mFloatVector1,
                message.mFloatVector2, message.mFloat1, message.mColor);
            break;

        case DebugRenderType::Cross:
            DebugRendererHelper::FillCross(
                bufferAdaptor, bufferData, message.mFloatVector1,
                message.mFloat1, message.mColor);
            break;

        case DebugRenderType::Line:
            DebugRendererHelper::FillLine(
                bufferAdaptor, bufferData, message.mFloatVector1,
                message.mFloatVector2, message.mColor);
            break;

        case DebugRenderType::Sphere:
            DebugRendererHelper::FillSphere(
                bufferAdaptor, bufferData, message.mFloatVector1,
                message.mFloat1, message.mColor);
            break;

        case DebugRenderType::Text:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION()
            break;

        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    mVertexResource->UnmapChannel();

    // Remove time-out message.
    mMessageManager->Update(elapsed);
}

}
