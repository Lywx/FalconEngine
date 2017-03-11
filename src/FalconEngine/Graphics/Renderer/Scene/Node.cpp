#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

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
    for (auto child : mChildrenSlot)
    {
        if (child)
        {
            child->mParent = nullptr;
        }
    }

    mChildrenSlot.clear();
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
Node::AttachChild(SpatialSharedPtr child)
{
    FALCON_ENGINE_CHECK_NULLPTR(child);

    if (child->mParent)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The child already has a parent.");
    }

    child->mParent = this;

    // Insert the child in the first available slot (if any).
    auto slotIndex = 0;
    for (auto iter = mChildrenSlot.begin(); iter != mChildrenSlot.end(); ++iter, ++slotIndex)
    {
        auto& slot = *iter;

        // Find a available slot
        if (slot == nullptr)
        {
            slot = child;
            return slotIndex;
        }
    }

    // All slots are used, so append the child to the array.
    slotIndex = int(mChildrenSlot.size());
    mChildrenSlot.push_back(child);
    return slotIndex;
}

int
Node::DetachChild(SpatialSharedPtr child)
{
    if (child)
    {
        auto slotIndex = 0;
        for (auto iter = mChildrenSlot.begin(); iter != mChildrenSlot.end(); ++iter, ++slotIndex)
        {
            auto& slot = *iter;
            if (slot == child)
            {
                slot->mParent = nullptr;

                // NTOE(Wuxiang): The detach operation would not change the vector
                // arrangement. Since the vector stores pointer, if you would just
                // erase the slot from the vector, the moving element happens
                // mostly when the node structure dynamically changes. This happens
                // in dynamic interaction. If the interaction cause the structure
                // change so often and so irregular, the cost of erasing slot would
                // be higher than simply set null to the slot.
                slot = nullptr;

                return slotIndex;
            }
        }
    }

    return -1;
}

SpatialSharedPtr
Node::DetachChildAt(size_t slotIndex)
{
    if (0 <= slotIndex && slotIndex < mChildrenSlot.size())
    {
        auto slot = mChildrenSlot[slotIndex];
        if (auto child = slot)
        {
            child->mParent = nullptr;
            mChildrenSlot[slotIndex] = nullptr;

            return child;
        }

        return nullptr;
    }

    return nullptr;
}

const Spatial *
Node::GetChildAt(size_t i) const
{
    return mChildrenSlot.at(i).get();
}

SpatialSharedPtr
Node::GetChildAt(size_t slotIndex)
{
    return mChildrenSlot.at(slotIndex);
}

SpatialSharedPtr
Node::SetChildAt(size_t slotIndex, SpatialSharedPtr child)
{
    // NOTE(Wuxiang): The child is allowed to be null so that you would be able
    // to clear the child from the children list.

    if (child && child->mParent)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The child already has a parent");
    }

    if (0 <= slotIndex && slotIndex < GetChildrenSlotNum())
    {
        auto& slot = mChildrenSlot[slotIndex];

        // Remove the child currently in the slot.
        auto childPrevious = slot;
        if (childPrevious)
        {
            childPrevious->mParent = nullptr;
        }

        // Insert the new child in the slot.
        if (child)
        {
            child->mParent = this;
        }

        slot = child;

        return childPrevious;
    }

    // The index is out of range, so append the child to the array.
    if (child)
    {
        child->mParent = this;
    }

    mChildrenSlot.push_back(child);

    return nullptr;
}

int
Node::GetChildrenNum() const
{
    auto childrenNum = 0;
    for (auto slotIndex = 0; slotIndex < GetChildrenSlotNum(); ++slotIndex)
    {
        if (GetChildAt(slotIndex) != nullptr)
        {
            ++childrenNum;
        }
    }

    return childrenNum;
}

int
Node::GetChildrenSlotNum() const
{
    return int(mChildrenSlot.size());
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Node::CopyTo(Node *lhs) const
{
    Spatial::CopyTo(lhs);

    // Clear existing children.
    for (auto slot : lhs->mChildrenSlot)
    {
        if (auto child = slot)
        {
            child->mParent = nullptr;
        }
    }

    lhs->mChildrenSlot.clear();

    // Create new children.
    for (int slotIndex = 0; slotIndex < GetChildrenSlotNum(); ++slotIndex)
    {
        auto slot = GetChildAt(slotIndex);
        if (auto child = slot)
        {
            auto childClone = child->GetClone();
            lhs->SetChildAt(slotIndex, shared_ptr<Spatial>(childClone));
        }
    }
}

Node *
Node::GetClone() const
{
    auto clone = new Node();
    CopyTo(clone);
    return clone;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Node::UpdateWorldTransform(double elapsed)
{
    Spatial::UpdateWorldTransform(elapsed);

    for (auto child : mChildrenSlot)
    {
        if (child)
        {
            child->Update(elapsed, false);
        }
    }
}

}
