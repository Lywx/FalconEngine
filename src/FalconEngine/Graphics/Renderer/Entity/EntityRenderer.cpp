#include <FalconEngine/Graphics/Renderer/Entity/EntityRenderer.h>

#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Visual.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Scene/Node.h>
#include <queue>

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
/* Public Members                                                       */
/************************************************************************/
void
EntityRenderer::Draw(const Entity *entity)
{
    mEntityList.push_back(entity);
}

void
EntityRenderer::Initialize()
{
}

void
EntityRenderer::RenderBegin()
{
    mEntityList.clear();
}

void
EntityRenderer::Render(Renderer *renderer, double percent)
{
    //queue<pair<const Node *, int>> taskCurrentQueue, taskNextQueue;
    //taskCurrentQueue.push(make_pair(root, 1));

    //while (!taskCurrentQueue.empty())
    //{
    //    // Initialize traversal result for this level.
    //    resultVector.push_back(vector<int>());

    //    // Complete traversing current level.
    //    while (!taskCurrentQueue.empty())
    //    {
    //        auto taskCurrent = taskCurrentQueue.front();
    //        auto *nodeCurrent = taskCurrent.first;
    //        auto &depthCurrent = taskCurrent.second;

    //        taskCurrentQueue.pop();

    //        // Visit the node.
    //        resultVector.back().push_back(nodeCurrent->val);

    //        if (nodeCurrent->left)
    //        {
    //            taskNextQueue.push(make_pair(nodeCurrent->left, depthCurrent + 1));
    //        }

    //        if (nodeCurrent->right)
    //        {
    //            taskNextQueue.push(make_pair(nodeCurrent->right, depthCurrent + 1));
    //        }
    //    }

    //    swap(taskCurrentQueue, taskNextQueue);
    //}


    for (auto entity : mEntityList)
    {
        auto node = entity->GetNode();
        auto nodeNum = node->ChildrenNum();
        for (auto nodeIndex = 0; nodeIndex < nodeNum; ++nodeIndex)
        {
            auto child = node->GetChildAt(nodeIndex);
            if (auto visual = dynamic_pointer_cast<Visual>(child))
            {
                renderer->Draw(visual.get());
            }
            //else if (auto entityChild = dynamic_pointer_cast<Entity>(child))
            //{
            //    Draw(entityChild.get());
            //}
        }
    }
}

void
EntityRenderer::RenderEnd()
{
}
}
