#include <FalconEngine/Graphics/Scene/Node.h>

#include <assimp/scene.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Node, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Node::Node()
{
}

Node::~Node()
{
    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
    {
        auto& spatialPtr = *iter;
        if (spatialPtr)
        {
            spatialPtr->mParent = nullptr;
            spatialPtr = nullptr;
        }
    }
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
Node::AttachChild(SpatialSharedPtr child)
{
    if (!child)
    {
        // You cannot attach null children to a node.
        assert(false);
        return -1;
    }

    if (child->mParent)
    {
        // The child already has a parent.
        assert(false);;
        return -1;
    }

    child->mParent = this;

    // Insert the child in the first available slot (if any).
    auto i = 0;
    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter, ++i)
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
    auto insertedIndex = int(mChildren.size());
    mChildren.push_back(child);
    return insertedIndex;
}

int
Node::DetachChild(SpatialSharedPtr child)
{
    if (child)
    {
        auto i = 0;
        for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter, ++i)
        {
            auto& spatialPtr = *iter;
            if (spatialPtr == child)
            {
                spatialPtr->mParent = nullptr;
                spatialPtr = nullptr;
                return i;
            }
        }
    }

    return -1;
}

SpatialSharedPtr
Node::DetachChildAt(size_t i)
{
    if (0 <= i && i < mChildren.size())
    {
        auto child = mChildren[i];
        if (child)
        {
            child->mParent = nullptr;
            mChildren[i] = nullptr;
        }

        return child;
    }

    return nullptr;
}

SpatialSharedPtr
Node::SetChild(size_t i, SpatialSharedPtr child)
{
    if (child)
    {
        // The child already has a parent
        assert(child->mParent);;
    }

    if (0 <= i && i < ChildrenNum())
    {
        // Remove the child currently in the slot.
        auto childPrevious = mChildren[i];
        if (childPrevious)
        {
            childPrevious->mParent = nullptr;
        }

        // Insert the new child in the slot.
        if (child)
        {
            child->mParent = this;
        }

        mChildren[i] = child;

        return childPrevious;
    }

    // The index is out of range, so append the child to the array.
    if (child)
    {
        child->mParent = this;
    }

    mChildren.push_back(child);

    return nullptr;
}

SpatialSharedPtr
Node::ChildAt(size_t i)
{
    if (0 <= i && i < ChildrenNum())
    {
        return mChildren[i];
    }

    return nullptr;
}

void
Node::UpdateWorldTransform(double elapsed)
{
    Spatial::UpdateWorldTransform(elapsed);

    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
    {
        auto child = *iter;
        if (child)
        {
            child->Update(elapsed, false);
        }
    }
}

}
