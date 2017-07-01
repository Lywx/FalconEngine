#pragma once

#include <FalconEngine/Core/Common.h>

#include <functional>

namespace FalconEngine
{

template <typename T>
using EventBinder = std::function<void(void *, T)>;

#pragma warning(disable: 4251)
template <typename T>
class EventCallback
{
public:
    EventCallback() :
        mBinder()
    {

    }

    EventCallback(const EventBinder<T> binder) :
        mBinder(binder)
    {
    }

public:
    EventBinder<T> mBinder;
};
#pragma warning(default: 4251)

}

