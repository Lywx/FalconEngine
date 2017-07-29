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
    mDebugBufferResource = make_shared<BufferResource<BufferResourceChannel>>();
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
    DebugRenderMessage message(DebugRenderType::AABB, color, duration, depthEnabled);
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
DebugRenderer::AddCamera(const Camera *camera)
{
    mDebugEffectParams->AddCamera(camera);
}

void
DebugRenderer::RemoveCamera(const Camera *camera)
{
    mDebugEffectParams->RemoveCamera(camera);
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
    mDebugBufferResource->Draw(nullptr);
}

void
DebugRenderer::RenderEnd()
{
    mDebugBufferResource->ResetPersistent();
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
        case DebugRenderType::AABB:
            mDebugBufferResource->AddChannelElement(
                channel, 24);
            break;
        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case DebugRenderType::Circle:
            mDebugBufferResource->AddChannelElement(
                channel, DebugRendererHelper::CircleSampleNum * 2);
            break;
        case DebugRenderType::Cross:
            mDebugBufferResource->AddChannelElement(
                channel, 6);
            break;
        case DebugRenderType::Line:
            mDebugBufferResource->AddChannelElement(
                channel, 2);
            break;
        case DebugRenderType::Sphere:
            mDebugBufferResource->AddChannelElement(
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

    mDebugBufferResource->FillDataBegin(
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

            // NOTE(Wuxiang): Text doesn't have a camera parameter. When
            // cameraIndex is invalid it will not be used.
            int cameraIndex = 0;
            if (message.mCamera)
            {
                cameraIndex = mDebugEffectParams->mCameraSlotTable.at(message.mCamera);
            }

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
                break;
            default:
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
        }
    }

    mDebugBufferResource->FillDataEnd();
    mDebugBufferResource->Reset();

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
