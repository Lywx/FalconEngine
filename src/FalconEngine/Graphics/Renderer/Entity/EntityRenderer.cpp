#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Graphics/Effects/BoundingBoxEffect.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Math/Bound/AABBBoundingBox.h>
#include <FalconEngine/Core/Memory.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
EntityRenderer::EntityRenderer()
{
}

EntityRenderer::~EntityRenderer()
{
}

/************************************************************************/
/* Rendering API                                                        */
/************************************************************************/
void
EntityRenderer::Draw(const Camera *camera, const Entity *entity)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    mEntityTable[camera].push_back(entity);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Entity *entity, Color boundingBoxColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    DrawBoundingBox(camera, entity->GetNode().get(), boundingBoxColor);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Node *node, Color boundingBoxColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(node);

    auto nodeChildNum = node->ChildrenNum();
    for (auto childIndex = 0; childIndex < nodeChildNum; ++childIndex)
    {
        const Spatial *child = node->GetChildAt(childIndex);
        if (auto childVisual = dynamic_cast<const Visual *>(child))
        {
            DrawBoundingBox(camera, childVisual, boundingBoxColor);
        }
        else if (auto childNode = dynamic_cast<const Node *>(child))
        {
            DrawBoundingBox(camera, childNode, boundingBoxColor);
        }
    }
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Visual *visual, Color boundingBoxColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);

    DrawBoundingBox(camera, visual, visual->GetBoundingBox(), boundingBoxColor);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);
    FALCON_ENGINE_CHECK_NULLPTR(boundingBox);

    auto batch = PrepareBatch(camera, boundingBox->GetPositionNum());
    PrepareBoundingBox(*batch, camera, visual, boundingBox, boundingBoxColor);
}

void
EntityRenderer::Initialize()
{
}

void
EntityRenderer::RenderBegin()
{
    // Clean every bucket in the entity table.
    for (auto& cameraEntityListPair : mEntityTable)
    {
        auto& entityList = cameraEntityListPair.second;
        entityList.clear();
    }

    // Reset batch in every bounding box batch.
    for (auto& cameraBoundingBoxBatchPair : mEntityBoundingBoxBatchTable)
    {
        auto& batch = cameraBoundingBoxBatchPair.second;
        batch->mVertexBufferDataIndex = 0;
        batch->mVertexNum = 0;

        batch->mTransformBufferDataIndex = 0;
    }
}

void
EntityRenderer::Render(Renderer *renderer, double percent)
{
    for (auto& cameraEntityListPair : mEntityTable)
    {
        auto camera = cameraEntityListPair.first;
        auto& entityList = cameraEntityListPair.second;

        // Prepare the level order traversal
        for (auto entity : entityList)
        {
            mNodeQueueCurrent.push(make_pair(entity->GetNode().get(), 1));
        }

        // Use level order traversal to render each visual in the hierarchy, which is not totally necessary.
        while (!mNodeQueueCurrent.empty())
        {
            // Complete traversing current level.
            while (!mNodeQueueCurrent.empty())
            {
                auto renderItemCurrent = mNodeQueueCurrent.front();
                auto renderNodeCurrent = renderItemCurrent.first;
                auto &sceneDepthCurrent = renderItemCurrent.second;

                mNodeQueueCurrent.pop();

                // Visit the children.
                auto nodeNum = renderNodeCurrent->ChildrenNum();
                for (auto childIndex = 0; childIndex < nodeNum; ++childIndex)
                {
                    auto child = renderNodeCurrent->GetChildAt(childIndex);
                    if (auto childVisual = dynamic_pointer_cast<Visual>(child))
                    {
                        renderer->Draw(camera, childVisual.get());
                    }
                    else if (auto childNode = dynamic_pointer_cast<Node>(child))
                    {
                        // Prepare for traversing next level.
                        mNodeQueueNext.push(make_pair(childNode.get(), sceneDepthCurrent + 1));
                    }
                }
            }

            std::swap(mNodeQueueCurrent, mNodeQueueNext);
        }
    }

    // Render bounding box.
    for (auto& cameraBoundingBoxBatchPair : mEntityBoundingBoxBatchTable)
    {
        auto& batch = cameraBoundingBoxBatchPair.second;
        if (batch->mVertexNum > 0)
        {
            // Update buffer data before drawing
            size_t transformNum = batch->mVertexNum / batch->mVertexTriangles->GetPrimitiveInstancingNum();
            batch->mTransformBuffer->SetElementNum(transformNum);
            renderer->Update(batch->mTransformBuffer.get());

            batch->mVertexBuffer->SetElementNum(batch->mVertexNum);
            renderer->Update(batch->mVertexBuffer.get());

            renderer->Draw(nullptr, batch->mVertexTriangles.get());
        }
    }
}

void
EntityRenderer::RenderEnd()
{
}

BoundingBoxBatchSharedPtr
EntityRenderer::PrepareBatch(const Camera *camera, size_t boundingBoxVertexNum)
{
    auto iter = mEntityBoundingBoxBatchTable.find(camera);
    if (iter != mEntityBoundingBoxBatchTable.end())
    {
        return iter->second;
    }

    static const size_t sBoundingBoxBufferSize = Kilobytes(100);
    static shared_ptr<BoundingBoxEffect> sBoungingBoxEffect;

    if (sBoungingBoxEffect == nullptr)
    {
        sBoungingBoxEffect = make_shared<BoundingBoxEffect>();
    }

    // TODO(Wuxiang): Add multiple type of bounding box support.
    auto boundingBoxVertexFormat = sBoungingBoxEffect->CreateVertexFormat(boundingBoxVertexNum);
    auto boundingBoxVertexBuffer = make_shared<VertexBuffer>(sBoundingBoxBufferSize, sizeof(BoundingBoxVertex), BufferUsage::Dynamic);
    auto boundingBoxVertexTransformBuffer = make_shared<VertexBuffer>(sBoundingBoxBufferSize, sizeof(BoundingBoxVertexTransform), BufferUsage::Dynamic);

    // Setup font specific visual quad.
    shared_ptr<Visual> boundingBoxTriangles;
    {
        auto vertexGroup = make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, boundingBoxVertexBuffer, 0, boundingBoxVertexFormat->GetVertexAttributeStride());
        vertexGroup->SetVertexBuffer(1, boundingBoxVertexTransformBuffer, 0, boundingBoxVertexFormat->GetVertexAttributeStride());

        auto boundingBoxEffectInstance = make_shared<VisualEffectInstance>(sBoungingBoxEffect);
        sBoungingBoxEffect->CreateInstance(boundingBoxEffectInstance.get(), camera);

        auto boundingBoxPrimitiveTriangles = make_shared<PrimitiveTriangles>(boundingBoxVertexFormat, vertexGroup);
        boundingBoxTriangles = make_shared<Visual>(boundingBoxPrimitiveTriangles);
        boundingBoxTriangles->SetEffectInstance(boundingBoxEffectInstance);
    }

    auto boundingBoxBatch = make_shared<BoundingBoxBatch>(camera, boundingBoxVertexBuffer, boundingBoxTriangles, boundingBoxVertexTransformBuffer);
    mEntityBoundingBoxBatchTable.insert({ camera, boundingBoxBatch });
    return boundingBoxBatch;
}

void
FillBufferBoundingBoxVertex(
    _IN_     const BoundingBox *boundingBox,
    _IN_     const Vector4f     vertexColor,
    _IN_OUT_ size_t&            vertexBufferDataIndex,
    _IN_OUT_ float             *vertexBufferData)
{
    for (auto vertexPosition : boundingBox->GetPositionList())
    {
        FillBufferDataAsVector3f(vertexBufferData, vertexBufferDataIndex, vertexPosition);
        FillBufferDataAsVector4f(vertexBufferData, vertexBufferDataIndex, vertexColor);
    }
}

void
FillBufferBoundingBoxTransform(
    _IN_     const Visual   *visual,
    _IN_     const Matrix4f& viewProjectionTransform,
    _IN_OUT_ size_t&         transformBufferDataIndex,
    _IN_OUT_ float          *transformBufferData)
{
    Matrix4f modelViewProjectionTransform = viewProjectionTransform * visual->mWorldTransform;;
    FillBufferDataAsMatrix4f(transformBufferData, transformBufferDataIndex, modelViewProjectionTransform);
}

void
EntityRenderer::PrepareBoundingBox(BoundingBoxBatch& batch, const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor)
{
    auto boundingBoxVertexNum = boundingBox->GetPositionNum();;
    batch.mVertexNum += boundingBoxVertexNum;

    // NOTE(Wuxiang): Notice that it is assumed that this method is only called
    // during rendering so that the camera transform stops updating and is
    // guaranteed to be fixed.

    // Compute view projection transform for the camera.
    if (!batch.mCameraViewProjectionComputed)
    {
        batch.mCameraViewProjectionTransform = camera->GetProjection() * camera->GetView();
        batch.mCameraViewProjectionComputed = true;
    }

    // Fill the vertex attribute into the buffer.
    FillBufferBoundingBoxVertex(boundingBox, Vector4f(boundingBoxColor),
                                batch.mVertexBufferDataIndex,
                                reinterpret_cast<float *>(batch.mVertexBuffer->GetData()));

    FillBufferBoundingBoxTransform(visual,
                                   batch.mCameraViewProjectionTransform,
                                   batch.mTransformBufferDataIndex,
                                   reinterpret_cast<float *>(batch.mTransformBuffer->GetData()));
}

}
