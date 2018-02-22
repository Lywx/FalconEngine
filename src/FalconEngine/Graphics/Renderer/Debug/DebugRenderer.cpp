#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugRenderer::DebugRenderer() :
    mDebugFont(nullptr)
{
    mDebugBufferGroup = make_shared<BufferGroup<BufferChannel>>();
    mDebugEffectParams = make_shared<DebugEffectParams>();
    mDebugMessageManager = make_shared<DebugRenderMessageManager>();
}

DebugRenderer::~DebugRenderer()
{
}

enum BufferChannelName
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
DebugRenderer::AddAabb(const Camera *camera,
                       const Entity *entity,
                       const Color&  color,
                       float         duration,
                       bool          depthEnabled)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    AddAabb(camera, entity->GetNode(), color, duration, depthEnabled);
}

void
DebugRenderer::AddAabb(const Camera *camera,
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
            AddAabb(camera, childVisual, color, duration, depthEnabled);
        }
        else if (auto childNode = dynamic_cast<const Node *>(child))
        {
            AddAabb(camera, childNode, color, duration, depthEnabled);
        }
        else
        {
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }
}

void
DebugRenderer::AddAabb(const Camera *camera,
                       const Visual *visual,
                       const Color&  color,
                       float         duration,
                       bool          depthEnabled)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);

    auto aabb = visual->GetMesh()->GetAabb();

    AddAabb(camera,
            Vector3f(visual->mWorldTransform * Vector4f(aabb->mMin, 1)),
            Vector3f(visual->mWorldTransform * Vector4f(aabb->mMax, 1)),
            color, duration, depthEnabled);
}

void
DebugRenderer::AddAabb(const Camera   *camera,
                       const Vector3f& min,
                       const Vector3f& max,

                       const Color&    color,
                       float           duration,
                       bool            depthEnabled)
{
    DebugRenderMessage message(DebugRenderType::Aabb, color, duration, depthEnabled);
    message.mCamera = camera;
    message.mFloatVector1 = min;
    message.mFloatVector2 = max;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
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
    DebugRenderMessage message(DebugRenderType::Circle, color, duration, depthEnabled);
    message.mCamera = camera;
    message.mFloat1 = radius;
    message.mFloatVector1 = center;
    message.mFloatVector2 = normal;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
}

void
DebugRenderer::AddCross(const Camera   *camera,
                        const Vector3f& center,
                        float           radius,

                        const Color&    color,
                        float           duration,
                        bool            depthEnabled)
{
    DebugRenderMessage message(DebugRenderType::Cross, color, duration, depthEnabled);
    message.mCamera = camera;
    message.mFloat1 = radius;
    message.mFloatVector1 = center;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
}

void
DebugRenderer::AddLine(const Camera   *camera,
                       const Vector3f& from,
                       const Vector3f& to,

                       const Color&    color,
                       float           duration,
                       bool            depthEnabled)
{
    DebugRenderMessage message(DebugRenderType::Line, color, duration, depthEnabled);
    message.mCamera = camera;
    message.mFloatVector1 = from;
    message.mFloatVector2 = to;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
}

void
DebugRenderer::AddSphere(const Camera   *camera,
                         const Vector3f& center,
                         float           radius,

                         const Color&    color,
                         float           duration,
                         bool            depthEnabled)
{
    DebugRenderMessage message(DebugRenderType::Sphere, color, duration, depthEnabled);
    message.mCamera = camera;
    message.mFloat1 = radius;
    message.mFloatVector1 = center;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
}

void
DebugRenderer::AddText(const std::string& text,
                       const Vector2f&    textPosition,
                       float              fontSize,
                       const Color&       color,
                       float              duration,
                       bool               depthEnabled,
                       float              textLineWidth)
{
    DebugRenderMessage message(DebugRenderType::Text, color, duration, depthEnabled);
    message.mFloat1 = fontSize;
    message.mFloat2 = textLineWidth;
    message.mFloatVector1 = Vector3f(textPosition, 0);
    message.mString1 = text;

    mDebugMessageManager->mMessageList.push_back(std::move(message));
}

/************************************************************************/
/* Camera API                                                           */
/************************************************************************/
void
DebugRenderer::SetCamera(const Camera *camera)
{
    mDebugEffectParams->mCamera = camera;

    UpdateCamera();
}

void
DebugRenderer::UpdateCamera()
{
    auto data = mDebugEffectParams->mCameraBuffer->GetDataCast();
    data->mViewProjectionTransform = mDebugEffectParams->mCamera->GetViewProjection();
    mDebugEffectParams->mCameraBuffer->SignalContext();
}

/************************************************************************/
/* Rendering Engine API                                                 */
/************************************************************************/
void
DebugRenderer::Initialize()
{
    // Allocate necessary resource.
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

    // Load necessary asset.
    static auto sAssetManager = AssetManager::GetInstance();
    mDebugFont = sAssetManager->LoadFont("Content/Font/LuciadaConsoleDistanceField.fnt.bin").get();
}

void
DebugRenderer::RenderBegin()
{
}

void
DebugRenderer::Render(double /* percent */)
{
    mDebugBufferGroup->Draw(nullptr);
}

void
DebugRenderer::RenderEnd()
{
    mDebugBufferGroup->ResetPersistent();
}

void
DebugRenderer::UpdateFrame(double elapsed)
{
    static auto sFontRenderer = FontRenderer::GetInstance();

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
        case DebugRenderType::Aabb:
            mDebugBufferGroup->AddChannelElement(
                channel, 24);
            break;
        case DebugRenderType::Obb:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case DebugRenderType::Circle:
            mDebugBufferGroup->AddChannelElement(
                channel, DebugRendererHelper::CircleSampleNum * 2);
            break;
        case DebugRenderType::Cross:
            mDebugBufferGroup->AddChannelElement(
                channel, 6);
            break;
        case DebugRenderType::Line:
            mDebugBufferGroup->AddChannelElement(
                channel, 2);
            break;
        case DebugRenderType::Sphere:
            mDebugBufferGroup->AddChannelElement(
                channel, DebugRendererHelper::SpherePhiSampleNum
                * DebugRendererHelper::SphereThetaSampleNum * 6);
            break;
        case DebugRenderType::Text:
            sFontRenderer->AddText(
                mDebugFont, message.mFloat1, Vector2f(message.mFloatVector1),
                message.mString1, message.mColor, message.mFloat2);
            break;
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    mDebugBufferGroup->FillDataBegin(
        ResourceMapAccessMode::WriteBuffer,
        ResourceMapFlushMode::Automatic,
        ResourceMapSyncMode::Unsynchronized);

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
            std::tie(bufferAdaptor, bufferData) = mDebugBufferGroup->GetChannelData(channel);

            // Fill vertex data by inspecting the message.
            switch (message.mType)
            {
            case DebugRenderType::Aabb:
                DebugRendererHelper::FillAabb(
                    bufferAdaptor, bufferData, message.mFloatVector1,
                    message.mFloatVector2, message.mColor);
                break;
            case DebugRenderType::Obb:
                FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
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
                break;
            default:
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
        }
    }

    mDebugBufferGroup->FillDataEnd();
    mDebugBufferGroup->Reset();

    // Remove time-out message.
    mDebugMessageManager->UpdateFrame(elapsed);

    // Update transform uniform.
    UpdateCamera();
}

}
