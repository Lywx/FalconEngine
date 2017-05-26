#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Graphics/Effect/AABBEffect.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
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

    mEntityListTable[camera].push_back(entity);
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

    auto slotNum = node->GetChildrenSlotNum();
    for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
    {
        auto child = node->GetChildAt(slotIndex);
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

    DrawBoundingBox(camera, visual, visual->GetMesh()->GetBoundingBox(), boundingBoxColor);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);
    FALCON_ENGINE_CHECK_NULLPTR(boundingBox);

    auto batch = PrepareBatch(camera);
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
    for (auto& cameraEntityListPair : mEntityListTable)
    {
        auto& entityList = cameraEntityListPair.second;
        entityList.clear();
    }

    // Reset batch in every bounding box batch.
    for (auto& cameraBoundingBoxBatchPair : mBoundingBoxBatchTable)
    {
        auto& batch = cameraBoundingBoxBatchPair.second;
        batch->mCameraViewProjectionComputed = false;
        batch->mInstanceBufferDataIndex = 0;
        batch->mInstanceNum = 0;
    }
}

void
EntityRenderer::Render(Renderer *renderer, double /* percent */)
{
    // Render visuals.
    for (auto& cameraEntityListPair : mEntityListTable)
    {
        std::queue<std::pair<Node *, int>> nodeQueueCurrent;
        std::queue<std::pair<Node *, int>> nodeQueueNext;

        auto camera = cameraEntityListPair.first;
        auto& entityList = cameraEntityListPair.second;

        // Prepare the level order traversal
        for (auto entity : entityList)
        {
            nodeQueueCurrent.push(make_pair(entity->GetNode().get(), 1));
        }

        // Use level order traversal to render each visual in the hierarchy, which is not totally necessary.
        while (!nodeQueueCurrent.empty())
        {
            // Complete traversing current level.
            while (!nodeQueueCurrent.empty())
            {
                auto renderItemCurrent = nodeQueueCurrent.front();
                auto renderNodeCurrent = renderItemCurrent.first;
                auto &sceneDepthCurrent = renderItemCurrent.second;

                nodeQueueCurrent.pop();

                // Visit the children.
                auto slotNum = renderNodeCurrent->GetChildrenSlotNum();
                for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
                {
                    auto child = renderNodeCurrent->GetChildAt(slotIndex);
                    if (auto childVisual = dynamic_pointer_cast<Visual>(child))
                    {
                        renderer->Draw(camera, childVisual.get());
                    }
                    else if (auto childNode = dynamic_pointer_cast<Node>(child))
                    {
                        // Prepare for traversing next level.
                        nodeQueueNext.push(make_pair(childNode.get(), sceneDepthCurrent + 1));
                    }
                    else
                    {
                        // Scene graph only consists of two type of spatial objects:
                        // either Node or Visual.
                        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
                    }
                }
            }

            std::swap(nodeQueueCurrent, nodeQueueNext);
        }
    }

    // Render bounding boxes.
    for (auto& cameraBoundingBoxBatchPair : mBoundingBoxBatchTable)
    {
        auto *camera = cameraBoundingBoxBatchPair.first;
        auto& batch = cameraBoundingBoxBatchPair.second;
        if (batch->mInstanceNum > 0)
        {
            // Update buffer data before drawing
            int instanceNum = batch->mInstanceNum;
            batch->mInstanceBuffer->SetElementNum(instanceNum);
            renderer->Update(batch->mInstanceBuffer.get());

            // NOTE(Wuxiang): Don't need to update buffer that stores fixed vertex data.
            static auto sVerterBufferUpdated = false;
            if (!sVerterBufferUpdated)
            {
                renderer->Update(batch->mVertexBuffer.get());
                sVerterBufferUpdated = true;
            }

            // Update instancing data.
            batch->mVisualEffectInstance->SetShaderInstancingNum(0, instanceNum);
            renderer->Draw(camera, batch->mVisual.get());
        }
    }
}

void
EntityRenderer::RenderEnd()
{
}

// @summary Fill vertex buffer with one set of cube (length = 2, centered at origin)'s model position.
void
FillBufferBoundingBoxPosition(VertexBuffer *vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    size_t bufferDataIndex = 0;
    auto *bufferData = vertexBuffer->GetData();

    // NOTE(Wuxiang): The idea is to use cube position and each bounding box
    // specific transform matrix to generate AABB bounding box's coordinates
    // so that you can use single instancing draw call to draw all the AABB bounding box.
    static auto cubeModelPositionList = AABBBoundingBox::GetCubeModelPositionList();
    for (auto position : cubeModelPositionList)
    {
        FillBufferDataAsVector3f<float>(reinterpret_cast<float *>(bufferData), bufferDataIndex, position);
    }
}

void
FillBufferBoundingBoxColor(
    _IN_     const Vector4f     vertexColor,
    _IN_OUT_ size_t&            vertexBufferDataIndex,
    _IN_OUT_ float             *vertexBufferData)
{
    FillBufferDataAsVector4f<float>(vertexBufferData, vertexBufferDataIndex, vertexColor);
}

void
FillBufferAABBBoundingBoxTransform(
    _IN_     const Matrix4f&        viewProjectionTransform,
    _IN_     const AABBBoundingBox *boundingBox,
    _IN_     const Matrix4f&        modelTransform,
    _IN_OUT_ size_t&                transformBufferDataIndex,
    _IN_OUT_ float                 *transformBufferData)
{
    FALCON_ENGINE_CHECK_NULLPTR(boundingBox);

    Matrix4f modelViewProjectionTransform = viewProjectionTransform
                                            * modelTransform
                                            * boundingBox->GetCubeModelPositionTransform();
    FillBufferDataAsMatrix4f<float>(transformBufferData, transformBufferDataIndex, modelViewProjectionTransform);
}

shared_ptr<VertexBuffer>
CreateBoundingBoxVertexBuffer(int aabbBoundingBoxVertexNum)
{
    auto boundingBoxVertexBuffer = make_shared<VertexBuffer>(aabbBoundingBoxVertexNum, sizeof(AABBBoundingBoxVertex), BufferUsage::Static);

    // Prepare vertex buffer data.
    FillBufferBoundingBoxPosition(boundingBoxVertexBuffer.get());

    return boundingBoxVertexBuffer;
};

std::shared_ptr<AABBBoundingBoxBatch>
EntityRenderer::PrepareBatch(const Camera *camera)
{
    // Find existing batch for that camera.
    {
        auto iter = mBoundingBoxBatchTable.find(camera);
        if (iter != mBoundingBoxBatchTable.end())
        {
            return iter->second;
        }
    }

    // Initialize new batch for given camera.
    {
        auto aABBBoundingBoxInstanceNum = int(Kilobytes(1));
        auto aABBBoundingBoxVertexNum = 24;
        auto aABBBoungingBoxEffect = make_shared<AABBEffect>();

        // TODO(Wuxiang): Add multiple type of bounding box support.

        // Hold fixed data about vertex position in model space.
        auto aABBBoundingBoxVertexBuffer = CreateBoundingBoxVertexBuffer(aABBBoundingBoxVertexNum);

        // Hold dynamic data about each instance of bounding box.
        auto aABBBoundingBoxInstanceBuffer = make_shared<VertexBuffer>(aABBBoundingBoxInstanceNum, sizeof(AABBBoundingBoxInstance), BufferUsage::Dynamic);

        // AABB bounding box is bipartite graph, so you could not use line strip.
        auto aABBBoundingBoxPrimitive = make_shared<PrimitiveLines>(aABBBoundingBoxVertexBuffer, false);
        auto aABBBoundingBoxMesh = make_shared<Mesh>(aABBBoundingBoxPrimitive, nullptr);
        auto aABBBoundingBoxVisual = make_shared<Visual>(aABBBoundingBoxMesh);
        auto aABBBoundingBoxVisualEffectInstance = aABBBoungingBoxEffect->CreateInstance(aABBBoundingBoxVisual.get(), aABBBoundingBoxInstanceBuffer);

        auto aABBBoundingBoxBatch = make_shared<AABBBoundingBoxBatch>(camera, aABBBoundingBoxVertexBuffer, aABBBoundingBoxInstanceBuffer, aABBBoundingBoxVisual, aABBBoundingBoxVisualEffectInstance);
        mBoundingBoxBatchTable.insert({ camera, aABBBoundingBoxBatch });
        return aABBBoundingBoxBatch;
    }
}

void
EntityRenderer::PrepareBoundingBox(AABBBoundingBoxBatch& batch, const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor)
{
    ++batch.mInstanceNum;

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
    {
        // Fill vertex color.
        FillBufferBoundingBoxColor(Vector4f(boundingBoxColor),
                                   batch.mInstanceBufferDataIndex,
                                   reinterpret_cast<float *>(batch.mInstanceBuffer->GetData()));

        // Fill vertex transform.
        if (auto aabbBoundingBox = dynamic_cast<const AABBBoundingBox *>(boundingBox))
        {
            FillBufferAABBBoundingBoxTransform(
                batch.mCameraViewProjectionTransform,
                aabbBoundingBox,
                visual->mWorldTransform,
                batch.mInstanceBufferDataIndex,
                reinterpret_cast<float *>(batch.mInstanceBuffer->GetData()));
        }
        else
        {
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        }
    }
}

}
