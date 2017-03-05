#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Math/Bound/AABBBoundingBox.h>

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
    mEntityRenderTable[camera].push_back(entity);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const BoundingBox *boundingBox)
{
    mBoundingBoxRenderTable[camera].push_back(boundingBox);
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Entity *entity)
{
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Node *node)
{
}

void
EntityRenderer::DrawBoundingBox(const Camera *camera, const Visual *visual)
{
}

void
EntityRenderer::Initialize()
{
}

void
EntityRenderer::RenderBegin()
{
    // Clean every bucket in the bounding box table.
    for (auto& cameraBoundingBoxListPair : mBoundingBoxRenderTable)
    {
        auto& boundingBoxList = cameraBoundingBoxListPair.second;
        boundingBoxList.clear();
    }

    // Clean every bucket in the entity table.
    for (auto& cameraEntityListPair : mEntityRenderTable)
    {
        auto& entityList = cameraEntityListPair.second;
        entityList.clear();
    }
}

void
EntityRenderer::Render(Renderer *renderer, double percent)
{
    // TODO(Wuxiang): Replace it with normal traversal
    for (auto& cameraEntityListPair : mEntityRenderTable)
    {
        auto camera = cameraEntityListPair.first;
        auto& entityList = cameraEntityListPair.second;

        for (auto entity : entityList)
        {
            mNodeRenderQueueCurrent.push(make_pair(entity->GetNode().get(), 1));
        }

        // NOTE(Wuxiang): Use level order traversal to render each visual in the hierarchy.
        while (!mNodeRenderQueueCurrent.empty())
        {
            // Complete traversing current level.
            while (!mNodeRenderQueueCurrent.empty())
            {
                auto renderItemCurrent = mNodeRenderQueueCurrent.front();
                auto renderNodeCurrent = renderItemCurrent.first;
                auto &sceneDepthCurrent = renderItemCurrent.second;

                mNodeRenderQueueCurrent.pop();

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
                        mNodeRenderQueueNext.push(make_pair(childNode.get(), sceneDepthCurrent + 1));
                    }
                }
            }

            swap(mNodeRenderQueueCurrent, mNodeRenderQueueNext);
        }
    }
}

void
EntityRenderer::RenderEnd()
{
}
}
