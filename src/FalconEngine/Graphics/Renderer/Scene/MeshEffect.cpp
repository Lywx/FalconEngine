#include <FalconEngine/Graphics/Renderer/Scene/MeshEffect.h>

#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(MeshEffect, VisualEffect);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MeshEffect::MeshEffect()
{
}

MeshEffect::~MeshEffect()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
MeshEffect::TraverseLevelOrder(Node *meshRoot, std::function<void(Mesh *)> meshOperation)
{
    using namespace std;

    // Use level order traversal to complete operation on each mesh.
    mNodeQueueCurrent.push(make_pair(meshRoot, 1));
    while (!mNodeQueueCurrent.empty())
    {
        // Complete traversing current level.
        while (!mNodeQueueCurrent.empty())
        {
            auto renderItemCurrent = mNodeQueueCurrent.front();
            auto renderNodeCurrent = renderItemCurrent.first;
            auto& sceneDepthCurrent = renderItemCurrent.second;

            mNodeQueueCurrent.pop();

            // Visit the children.
            auto nodeNum = renderNodeCurrent->ChildrenNum();
            for (auto childIndex = 0; childIndex < nodeNum; ++childIndex)
            {
                auto child = renderNodeCurrent->GetChildAt(childIndex);
                if (auto mesh = dynamic_pointer_cast<Mesh>(child))
                {
                    meshOperation(mesh.get());
                }
                else if (auto childNode = dynamic_pointer_cast<Node>(child))
                {
                    // Prepare for traversing next level.
                    mNodeQueueNext.push(make_pair(childNode.get(), sceneDepthCurrent + 1));
                }
            }
        }

        swap(mNodeQueueCurrent, mNodeQueueNext);
    }
}

}
