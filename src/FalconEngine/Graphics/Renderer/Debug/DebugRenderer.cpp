#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>

#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRendererHelper.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferController.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Math/AABB.h>
#include <FalconEngine/Math/Color.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
}

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
    mDebugMessageManager.mMessageList.emplace_back(DebugRenderType::AABB, 0.f,
            min, max, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddCircle(const Vector3f& center, const Vector3f& normal, float radius, const Color& color, float duration, bool depthEnabled)
{
    mDebugMessageManager.mMessageList.emplace_back(DebugRenderType::Circle, radius,
            center, normal, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddCross(const Vector3f& center, float radius, const Color& color, float duration, bool depthEnabled)
{
    mDebugMessageManager.mMessageList.emplace_back(DebugRenderType::Cross, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

void
DebugRenderer::AddLine(const Vector3f& from, const Vector3f& to, const Color& color, float duration, bool depthEnabled)
{
    mDebugMessageManager.mMessageList.emplace_back(DebugRenderType::Line, 0.f,
            from, to, color, duration,
            depthEnabled);
}

void
DebugRenderer::AddSphere(const Vector3f& center, float radius, const Color& color, float duration, bool depthEnabled)
{
    mDebugMessageManager.mMessageList.emplace_back(DebugRenderType::Sphere, radius,
            center, Vector3f::Zero, color,
            duration, depthEnabled);
}

/************************************************************************/
/* Rendering Engine API                                                 */
/************************************************************************/

void
DebugRenderer::Initialize()
{
    mDebugLineBatch[0] = DebugRendererHelper::CreateBatch(make_shared<DebugEffect>(false));
    mDebugLineBatch[1] = DebugRendererHelper::CreateBatch(make_shared<DebugEffect>(true));
}

void
DebugRenderer::RenderBegin()
{
    mDebugLineBatch->mLineNum = 0;
    mDebugLineBatch->mVertexBufferDataIndex = 0;
}

void
DebugRenderer::Render(Renderer *renderer, double percent)
{
    if (mDebugLineBatch->mLineNum > 0)
    {
        // Update buffer data before drawing
        int vertexNum = mDebugLineBatch->mLineNum * 2;
        mDebugLineBatch->mVertexBuffer->SetElementNum(vertexNum);
        renderer->Update(mDebugLineBatch->mVertexBuffer.get());
        renderer->Draw(nullptr, mDebugLineBatch->mLines.get());
    }
}

void
DebugRenderer::RenderEnd()
{
}

enum BufferChannel
{
    BufferChannel_PrimitiveLine = 0,
    BufferChannel_PrimitiveTriangle = 1,
};

void
DebugRenderer::Update(double elapsed)
{
    static auto sMasterRenderer = Renderer::GetInstance();

    auto bufferController = new BufferController();

    auto buffer = make_shared<VertexBuffer>();
    bufferController->CreateChannel(BufferChannel_PrimitiveLine,
                                    make_shared<BufferCircular>(buffer,
                                            buffer->GetCapacitySize() / 4));

    int64_t lineVertexNumList[2] = { 0, 0 };
    int64_t triangleVertexNumList[2] = { 0, 0 };

    // Compute mapped buffer size.
    UpdateMappedSize();

    for (auto& message : mDebugMessageManager->mMessageList)
    {
        auto batchIndex = message.mDepthEnabled ? 1 : 0;

        switch (message.mType)
        {
        case DebugRenderType::AABB:
            lineVertexNumList[batchIndex] += 24;
            break;

        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;

        case DebugRenderType::Circle:
            lineVertexNumList[batchIndex] += DebugRendererHelper::CircleSampleNum * 2;
            break;

        case DebugRenderType::Cross:
            lineVertexNumList[batchIndex] += 4;
            break;

        case DebugRenderType::Line:
            lineVertexNumList[batchIndex] += 2;
            break;

        case DebugRenderType::Sphere:
            triangleVertexNumList[batchIndex] += DebugRendererHelper::SphereSampleNum * 2;
            break;

        case DebugRenderType::Text:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;

        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

    unsigned char *bufferDataList[2];

    // Map buffers for all batches.
    for (auto batchIndex = 0; batchIndex < 2; ++batchIndex)
    {
        auto batch = mDebugLineBatch[batchIndex];

        auto buffer = batch->mLineVertexBuffer;
        auto bufferAdaptor = batch->mLineVertexBufferAdaptor;
        bufferDataList[batchIndex] = static_cast<unsigned char *>(
                                         sMasterRenderer->Map(
                                             buffer.get(),
                                             BufferAccessMode::WriteBuffer,
                                             BufferFlushMode::Automatic,
                                             BufferSynchronizationMode::Unsynchronized,
                                             buffer->GetDataOffset(),
                                             lineVertexNumList[batchIndex] * sizeof(DebugVertex)));
    }

    for (auto& message : mDebugMessageManager->mMessageList)
    {
        // Get the batch this message need to reside.
        auto batchIndex = message.mDepthEnabled ? 1 : 0;
        auto batch = mDebugLineBatch[batchIndex];

        auto bufferAdaptor = batch->mLineVertexBufferAdaptor;

        switch (message.mType)
        {
        case DebugRenderType::AABB:
            DebugRendererHelper::FillAABB(bufferAdaptor,
                                          bufferDataList[batchIndex], message.mFloatVector1,
                                          message.mFloatVector2, message.mColor);
            break;

        case DebugRenderType::OBB:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
            break;

        case DebugRenderType::Circle:
            DebugRendererHelper::FillCircle(bufferAdaptor,
                                            bufferDataList[batchIndex], message.mFloatVector1,
                                            message.mFloatVector2, message.mFloat1,
                                            message.mColor);
            break;

        case DebugRenderType::Cross:
            DebugRendererHelper::FillCross(bufferAdaptor,
                                           bufferDataList[batchIndex], message.mFloatVector1,
                                           message.mFloat1, message.mColor);
            break;

        case DebugRenderType::Line:
            DebugRendererHelper::FillLine(bufferAdaptor,
                                          bufferDataList[batchIndex], message.mFloatVector1,
                                          message.mFloatVector2, message.mColor);
            break;

        case DebugRenderType::Sphere:
            DebugRendererHelper::FillSphere(bufferAdaptor,
                                            bufferDataList[batchIndex], message.mFloatVector1,
                                            message.mFloat1, message.mColor);
            break;

        case DebugRenderType::Text:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION()
            break;

        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }

        // TODO(Wuxiang)
        bufferDataList[batchIndex];
    }

    // Remove time-out message.
    mDebugMessageManager->Update(elapsed);
}

}
