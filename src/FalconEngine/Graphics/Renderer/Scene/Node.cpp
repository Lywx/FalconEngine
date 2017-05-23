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
Node::AttachChild(std::shared_ptr<Spatial> child)
{
    FALCON_ENGINE_CHECK_NULLPTR(child);

    if (child->mParent)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The child already has a parent.");
    }

    child->mParent = this;

    // Insert the child in the first available slot (if any).
    auto slotIndex = 0;
    for (auto slotIter = mChildrenSlot.begin(); slotIter != mChildrenSlot.end(); ++slotIter, ++slotIndex)
    {
        auto& slot = *slotIter;

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
Node::DetachChild(std::shared_ptr<Spatial> child)
{
    if (child)
    {
        auto slotIndex = 0;
        for (auto slotIter = mChildrenSlot.begin(); slotIter != mChildrenSlot.end(); ++slotIter, ++slotIndex)
        {
            auto& slot = *slotIter;
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

std::shared_ptr<Spatial>
Node::DetachChildAt(int slotIndex)
{
    if (0 <= slotIndex && slotIndex < GetChildrenSlotNum())
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

void
Node::ClearChildrenSlot()
{
    mChildrenSlot.clear();
}

const Spatial *
Node::GetChildAt(int slotIndex) const
{
    if (0 <= slotIndex && slotIndex < GetChildrenSlotNum())
    {
        return mChildrenSlot.at(slotIndex).get();
    }

    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The slot index out of bound.");
}

std::shared_ptr<Spatial>
Node::GetChildAt(int slotIndex)
{
    if (0 <= slotIndex && slotIndex < GetChildrenSlotNum())
    {
        return mChildrenSlot.at(slotIndex);
    }

    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The slot index out of bound.");
}

std::shared_ptr<Spatial>
Node::SetChildAt(int slotIndex, std::shared_ptr<Spatial> child)
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

void
Node::Update(double elapsed, bool initiator)
{
    mUpdateBegun.Invoke(this, initiator);

    UpdateWorldTransform(elapsed);

    for (auto child : mChildrenSlot)
    {
        child->Update(elapsed, false);
    }

    mUpdateEnded.Invoke(this, initiator);
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Node::CopyTo(Node *lhs) const
{
    Spatial::CopyTo(lhs);

    // Clear existing children.
    {
        int slotNum = lhs->GetChildrenSlotNum();
        for (int slotIndex = 0; slotIndex < slotNum; ++slotIndex)
        {
            if (auto child = lhs->GetChildAt(slotIndex))
            {
                child->SetParent(nullptr);
            }
        }

        lhs->ClearChildrenSlot();
    }

    // Create new children.
    {
        int slotNum = GetChildrenSlotNum();
        for (int slotIndex = 0; slotIndex < slotNum; ++slotIndex)
        {
            auto slot = GetChildAt(slotIndex);
            if (auto child = slot)
            {
                auto childClone = child->GetClone();
                lhs->SetChildAt(slotIndex, shared_ptr<Spatial>(childClone));
            }
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

Node *
Node::GetClone(std::function<void(Node *lhs, Node *rhs)> copyTo)
{
    auto clone = new Node();
    copyTo(clone, this);
    return clone;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
Node::UpdateWorldTransform(double elapsed)
{
    // Mark children's world transform dirty.
    if (!mWorldTransformIsCurrent)
    {
        for (auto slot : mChildrenSlot)
        {
            if (auto child = slot)
            {
                child->mWorldTransformIsCurrent = false;
            }
        }
    }

    Spatial::UpdateWorldTransform(elapsed);
}

std::shared_ptr<Node>
ShareClone(std::shared_ptr<Node> node)
{
    return std::shared_ptr<Node>(node->GetClone());
}

}
