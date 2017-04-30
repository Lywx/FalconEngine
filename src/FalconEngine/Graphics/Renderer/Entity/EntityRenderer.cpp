#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Graphics/Effect/AABBBoundingBoxEffect.h>
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

    DrawBoundingBox(camera, visual, visual->GetBoundingBox(), boundingBoxColor);
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
    for (auto& cameraEntityListPair : mEntityTable)
    {
        auto& entityList = cameraEntityListPair.second;
        entityList.clear();
    }

    // Reset batch in every bounding box batch.
    for (auto& cameraBoundingBoxBatchPair : mEntityBoundingBoxBatchTable)
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
        auto *camera = cameraBoundingBoxBatchPair.first;
        auto& batch = cameraBoundingBoxBatchPair.second;
        if (batch->mInstanceNum > 0)
        {
            // Update buffer data before drawing
            size_t instanceNum = batch->mInstanceNum;
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
            batch->mVertexTriangles->SetEffectInstancingNum(instanceNum);
            renderer->Draw(camera, batch->mVertexTriangles.get());
        }
    }
}

void
EntityRenderer::RenderEnd()
{
}

// @summary Fill vertex buffer with one set of cube (length = 2, centered at origin)'s model position.
void
FillBufferBoundingBoxVertex(VertexBuffer *vertexBuffer)
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

BoundingBoxBatchSharedPtr
EntityRenderer::PrepareBatch(const Camera *camera)
{
    auto iter = mEntityBoundingBoxBatchTable.find(camera);
    if (iter != mEntityBoundingBoxBatchTable.end())
    {
        return iter->second;
    }

    static const size_t sAABBBoundingBoxInstanceNum = Kilobytes(1);
    static const size_t sAABBBoundingBoxVertexNum = 36;
    static shared_ptr<AABBBoundingBoxEffect> sBoungingBoxEffect;

    if (sBoungingBoxEffect == nullptr)
    {
        sBoungingBoxEffect = make_shared<AABBBoundingBoxEffect>();
    }

    // TODO(Wuxiang): Add multiple type of bounding box support.
    auto boundingBoxVertexFormat = sBoungingBoxEffect->CreateVertexFormat();

    // Hold fixed data about vertex position in model space.
    auto boundingBoxVertexBuffer = make_shared<VertexBuffer>(sAABBBoundingBoxVertexNum, sizeof(BoundingBoxVertex), BufferUsage::Static);

    // Prepare vertex buffer data.
    FillBufferBoundingBoxVertex(boundingBoxVertexBuffer.get());

    // Hold dynamic data about each instance of bounding box.
    auto boundingBoxIntanceBuffer = make_shared<VertexBuffer>(sAABBBoundingBoxInstanceNum, sizeof(BoundingBoxInstance), BufferUsage::Dynamic);

    // Setup font specific visual quad.
    shared_ptr<Visual> boundingBoxTriangles;
    {
        auto vertexGroup = make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, boundingBoxVertexBuffer, 0, boundingBoxVertexFormat->GetVertexAttributeStride(0));
        vertexGroup->SetVertexBuffer(1, boundingBoxIntanceBuffer, 0, boundingBoxVertexFormat->GetVertexAttributeStride(1));

        auto boundingBoxEffectInstance = make_shared<VisualEffectInstance>(sBoungingBoxEffect);
        sBoungingBoxEffect->CreateInstance(boundingBoxEffectInstance.get(), camera);

        auto boundingBoxPrimitiveTriangles = make_shared<PrimitiveTriangles>(boundingBoxVertexFormat, vertexGroup);
        boundingBoxTriangles = make_shared<Visual>(boundingBoxPrimitiveTriangles);
        boundingBoxTriangles->SetEffectInstance(boundingBoxEffectInstance);
    }

    auto boundingBoxBatch = make_shared<BoundingBoxBatch>(camera, boundingBoxVertexBuffer, boundingBoxTriangles, boundingBoxIntanceBuffer);
    mEntityBoundingBoxBatchTable.insert({ camera, boundingBoxBatch });
    return boundingBoxBatch;
}

void
EntityRenderer::PrepareBoundingBox(BoundingBoxBatch& batch, const Camera *camera, const Visual *visual, const BoundingBox *boundingBox, Color boundingBoxColor)
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
        if (auto aabb = dynamic_cast<const AABBBoundingBox *>(boundingBox))
        {
            FillBufferAABBBoundingBoxTransform(
                batch.mCameraViewProjectionTransform,
                aabb,
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
