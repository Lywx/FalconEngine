#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

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
EntityRenderer::Destroy()
{
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
}

void
EntityRenderer::Render(double /* percent */)
{
    static auto sMasterRenderer = Renderer::GetInstance();

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
                        sMasterRenderer->Draw(camera, childVisual);
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
}


}
