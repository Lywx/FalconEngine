#pragma once

#include <FalconEngine/CoreInclude.h>

#include <functional>

namespace FalconEngine
{

template <typename T>
using EventBinder = std::function<void(void *, T)>;

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

}

