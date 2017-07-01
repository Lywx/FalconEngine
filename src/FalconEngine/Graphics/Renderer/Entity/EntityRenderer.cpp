#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Core/Memory.h>
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
#include <FalconEngine/Math/Bound/AABB.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>

using namespace std;

namespace FalconEngine
{

class AABBBData
{
public:
    static shared_ptr<VertexBuffer>
    CreatePositionBuffer(int aabbVertexNum)
    {
        auto vertexBuffer = make_shared<VertexBuffer>(aabbVertexNum, sizeof(AABBVertex), BufferStorageMode::Host, BufferUsage::Static);

        FillPosition(vertexBuffer.get());

        return vertexBuffer;
    }

    // @summary Fill vertex buffer with one set of cube (length = 2, centered at origin)'s model position.
    static void
    FillPosition(VertexBuffer *vertexBuffer)
    {
        FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

        size_t bufferOffset = 0;
        auto *bufferData = vertexBuffer->GetData();

        // NOTE(Wuxiang): The idea is to use cube position and each bounding box
        // specific transform matrix to generate AABB bounding box's coordinates
        // so that you can use single instancing draw call to draw all the AABB bounding box.
        static auto unitModelPositionList = AABB::GetUnitPositionList();
        for (auto position : unitModelPositionList)
        {
            BufferData::Fill<Vector3f>(bufferData, bufferOffset, position);
        }
    }
};

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
EntityRenderer::DrawBoundingBox(const Camera *camera, const Entity *entity, const Color& color)
{
    FALCON_ENGINE_CHECK_NULLPTR(entity);

    DrawBoundingBox(camera, entity->GetNode(), color);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Node *node, const Color& color)
{
    FALCON_ENGINE_CHECK_NULLPTR(node);

    auto slotNum = node->GetChildrenSlotNum();
    for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
    {
        auto child = node->GetChildAt(slotIndex);
        if (auto childVisual = dynamic_cast<const Visual *>(child))
        {
            DrawBoundingBox(camera, childVisual, color);
        }
        else if (auto childNode = dynamic_cast<const Node *>(child))
        {
            DrawBoundingBox(camera, childNode, color);
        }
    }
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Visual *visual, const Color& color)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);

    auto batch = FindBoundingBoxBatch(camera);

    FillBoundingBox(*batch, camera, visual, color);
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
    for (auto& cameraBoundingBoxBatchPair : mEntityAABBBatchTable)
    {
        auto& batch = cameraBoundingBoxBatchPair.second;
        batch->mInstanceBufferCirculer->FillBegin();
        batch->mInstanceNum = 0;
    }
}

void
EntityRenderer::Render(double /* percent */)
{
    auto renderer = Renderer::GetInstance();

    // Render visuals.
    for (auto& cameraEntityListPair : mEntityListTable)
    {
        std::queue<std::pair<const Node *, int>> nodeQueueCurrent;
        std::queue<std::pair<const Node *, int>> nodeQueueNext;

        auto camera = cameraEntityListPair.first;
        auto& entityList = cameraEntityListPair.second;

        // Prepare the level order traversal
        for (auto entity : entityList)
        {
            nodeQueueCurrent.push(make_pair(entity->GetNode(), 1));
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
                    if (auto childVisual = dynamic_cast<const Visual *>(child))
                    {
                        renderer->Draw(camera, childVisual);
                    }
                    else if (auto childNode = dynamic_cast<const Node *>(child))
                    {
                        // Prepare for traversing next level.
                        nodeQueueNext.push(make_pair(childNode, sceneDepthCurrent + 1));
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
}

void
EntityRenderer::RenderEnd()
{
    for (auto& cameraBoundingBoxBatchPair : mEntityAABBBatchTable)
    {
        auto& batch = cameraBoundingBoxBatchPair.second;
        batch->mInstanceBufferCirculer->FillEnd();
    }
}


std::shared_ptr<EntityAABBBatch>
EntityRenderer::FindBoundingBoxBatch(const Camera *camera)
{
    // Find existing batch for that camera.
    {
        auto iter = mEntityAABBBatchTable.find(camera);
        if (iter != mEntityAABBBatchTable.end())
        {
            return iter->second;
        }
    }

    // Initialize new batch for given camera.
    {
        auto const BoundingBoxMaxNum = int(Kilobytes(1));

        auto visualEffect = make_shared<AABBEffect>();

        // Hold fixed data about vertex position in model space.
        auto vertexBuffer = AABBBData::CreatePositionBuffer(24);
        auto vertexFormat = visualEffect->GetVertexFormat();
        auto vertexGroup = make_shared<VertexGroup>();

        // Hold dynamic data about each instance of bounding box.
        auto instanceBuffer = make_shared<VertexBuffer>(BoundingBoxMaxNum,
                              sizeof(AABBInstance), BufferStorageMode::Host,
                              BufferUsage::Stream);

        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
        vertexGroup->SetVertexBuffer(1, instanceBuffer, 0, vertexFormat->GetVertexBufferStride(1));

        // AABB bounding box is bipartite graph, so you could not use line strip.
        auto primitive = make_shared<PrimitiveLines>(vertexFormat, vertexGroup, nullptr, false);

        auto visual = make_shared<Visual>(make_shared<Mesh>(primitive, nullptr));
        auto visualEffectParams = make_shared<AABBEffectParams>();
        auto visualEffectInstance = visualEffect->CreateInstance(visual.get(), visualEffectParams);

        auto batch = make_shared<EntityAABBBatch>(camera, vertexBuffer, instanceBuffer, visual, visualEffectInstance);
        mEntityAABBBatchTable.insert({ camera, batch });
        return batch;
    }
}

void
EntityRenderer::FillBoundingBox(EntityAABBBatch&   batch,
                                const Camera      *camera,
                                const Visual      *visual,
                                Color              color)
{
    ++batch.mInstanceNum;

    // NOTE(Wuxiang): Notice that it is assumed that this method is only called
    // during rendering so that the camera transform stops updating and is
    // guaranteed to be fixed.

    // Fill vertex color.
    batch.mInstanceBufferCirculer->FillAs<Color, Vector4f>(color);

    // Fill vertex transform.
    if (auto aabb = dynamic_cast<const AABB *>(visual->GetMesh()->GetBoundingBox()))
    {
        Matrix4f modelViewProjectionTransform =

            // Projection space aabb position.
            camera->GetViewProjection()

            // World space aabb position.
            * visual->mWorldTransform

            // Model space aabb position.
            * aabb->GetModelPositionTransform();

        batch.mInstanceBufferCirculer->Fill<Matrix4f>(modelViewProjectionTransform);
    }
    else
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

}
