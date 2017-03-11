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
            auto slotNum = renderNodeCurrent->GetChildrenSlotNum();
            for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
            {
                auto child = renderNodeCurrent->GetChildAt(slotIndex);
                if (auto childMesh = dynamic_pointer_cast<Mesh>(child))
                {
                    // Perform the given operation only on Mesh child.
                    meshOperation(childMesh.get());
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
