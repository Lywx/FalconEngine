#include <FalconEngine/Graphics/Scenes/Node.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(Node, Spatial);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Node::Node()
{
}

Node::~Node()
{
    for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
    {
        auto& spatialPtr = *iter;
        if (spatialPtr)
        {
            spatialPtr->Parent = nullptr;
            spatialPtr = nullptr;
        }
    }
}

int Node::AttachChild(SpatialPtr child)
{
    if (!child)
    {
        assert(false, "You cannot attach null children to a node.\n");
        return -1;
    }

    if (child->Parent)
    {
        assert(false, "The child already has a parent.\n");
        return -1;
    }

    child->Parent = this;

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
                spatialPtr->Parent = nullptr;
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
            child->Parent = nullptr;
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
        assert(child->Parent, "The child already has a parent.\n");
    }

    if (0 <= i && i < ChildrenNum())
    {
        // Remove the child currently in the slot.
        auto childPrevious = m_children[i];
        if (childPrevious)
        {
            childPrevious->Parent = nullptr;
        }

        // Insert the new child in the slot.
        if (child)
        {
            child->Parent = this;
        }

        m_children[i] = child;

        return childPrevious;
    }

    // The index is out of range, so append the child to the array.
    if (child)
    {
        child->Parent = this;
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

void Node::UpdateWorldBound()
{
    if (!WorldBoundIsCurrent)
    {
        // Start with an invalid bound.
        WorldBound.SetCenter(APoint::ORIGIN);
        WorldBound.SetRadius(0.0f);

        for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
        {
            auto child = *iter;
            if (child)
            {
                // GrowToContain ignores invalid child bounds.  If the world
                // bound is invalid and a child bound is valid, the child
                // bound is copied to the world bound.  If the world bound and
                // child bound are valid, the smallest bound containing both
                // bounds is assigned to the world bound.
                WorldBound.GrowToContain(child->WorldBound);
            }
        }
    }
}

}
