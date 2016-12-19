#include <FalconEngine/Graphics/Scenes/Node.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_IMPLEMENT_RTTI(Node, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Node::Node()
{
}

Node::Node(const aiScene *scene, const aiNode *node)
{
    // Process each mesh located at the current node
    for (size_t i = 0; i < node->mNumMeshes; ++i)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        AttachChild(make_shared<Mesh>(model, scene, scene->mMeshes[node->mMeshes[i]]));
    }

    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (size_t i = 0; i < node->mNumChildren; ++i)
    {
        AttachChild(make_shared<Node>(scene, node->mChildren[i]));
    }
}

Node::~Node()
{
    for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
    {
        auto& spatialPtr = *iter;
        if (spatialPtr)
        {
            spatialPtr->m_parent = nullptr;
            spatialPtr = nullptr;
        }
    }
}

int Node::AttachChild(SpatialPtr child)
{
    if (!child)
    {
        // You cannot attach null children to a node.
        assert(false);
        return -1;
    }

    if (child->m_parent)
    {
        // The child already has a parent.
        assert(false);;
        return -1;
    }

    child->m_parent = this;

    // Insert the child in the first available slot (if any).
    auto i = 0;
    for (auto iter = m_children.begin(); iter != m_children.end(); ++iter, ++i)
    {
        auto& spatialPtr = *iter;

        // Find a available slot
        if (!spatialPtr)
        {
            spatialPtr = child;
            return i;
        }
    }

    // All slots are used, so append the child to the array.
    auto insertedIndex = static_cast<int>(m_children.size());
    m_children.push_back(child);
    return insertedIndex;
}

int Node::DetachChild(SpatialPtr child)
{
    if (child)
    {
        auto i = 0;
        for (auto iter = m_children.begin(); iter != m_children.end(); ++iter, ++i)
        {
            auto& spatialPtr = *iter;
            if (spatialPtr == child)
            {
                spatialPtr->m_parent = nullptr;
                spatialPtr = nullptr;
                return i;
            }
        }
    }

    return -1;
}

SpatialPtr Node::DetachChildAt(size_t i)
{
    if (0 <= i && i < m_children.size())
    {
        auto child = m_children[i];
        if (child)
        {
            child->m_parent = nullptr;
            m_children[i] = nullptr;
        }

        return child;
    }

    return nullptr;
}

SpatialPtr Node::SetChild(size_t i, SpatialPtr child)
{
    if (child)
    {
        // The child already has a parent
        assert(child->m_parent);;
    }

    if (0 <= i && i < ChildrenNum())
    {
        // Remove the child currently in the slot.
        auto childPrevious = m_children[i];
        if (childPrevious)
        {
            childPrevious->m_parent = nullptr;
        }

        // Insert the new child in the slot.
        if (child)
        {
            child->m_parent = this;
        }

        m_children[i] = child;

        return childPrevious;
    }

    // The index is out of range, so append the child to the array.
    if (child)
    {
        child->m_parent = this;
    }

    m_children.push_back(child);

    return nullptr;
}

SpatialPtr Node::ChildAt(size_t i)
{
    if (0 <= i && i < ChildrenNum())
    {
        return m_children[i];
    }

    return nullptr;
}

void Node::UpdateWorldTransform(double elapsed)
{
    Spatial::UpdateWorldTransform(elapsed);

    for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
    {
        auto child = *iter;
        if (child)
        {
            child->Update(elapsed, false);
        }
    }
}

}
