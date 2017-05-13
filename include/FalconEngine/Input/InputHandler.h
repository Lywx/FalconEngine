#pragma once

#include <FalconEngine/Input/Header.h>
#include <FalconEngine/Core/EventHandler.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API InputPriority
{
    System = 0,
    User   = 1,
};

template <typename T>
class InputHandler : public EventHandler<T>
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    InputHandler(InputPriority priority) :
        mPriority(int(priority))
    {
    }

    virtual ~InputHandler() = default;

public:
    int GetPriority() const
    {
        return mPriority;
    }

private:
    int mPriority;
};

template <typename T>
inline bool
ComparePriority(const InputHandler<T> & lhs, const InputHandler<T> & rhs)
{
    if (lhs.GetPriority() < rhs.GetPriority())
    {
        return false;
    }

    if (lhs.GetPriority() > rhs.GetPriority())
    {
        return true;
    }

    return false;
}

}
