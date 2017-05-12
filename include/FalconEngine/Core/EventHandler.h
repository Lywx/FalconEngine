#pragma once

#include <FalconEngine/Core/Header.h>

#include <list>

#include <FalconEngine/Core/EventCallback.h>

namespace FalconEngine
{

template <typename T>
using EventCallbackList = std::list<EventCallback<T>*>;

// @ref Luis Sempe User Interface Programming for Games, 2014.
#pragma warning(disable: 4251)
template <typename T>
class EventHandler
{
public:
    EventHandler();
    virtual ~EventHandler();

public:
    typename EventCallbackList<T>::iterator
    operator += (EventCallback<T> *callback)
    {
        mCallbackList.emplace_front(callback);
        return mCallbackList.begin();
    }

    void
    operator -= (EventCallback<T> *callback)
    {
        mCallbackList.remove(callback);
    }

    void
    Invoke(void *sender, T data)
    {
        for (auto callback : mCallbackList)
        {
            callback->mBinder(sender, data);
        }
    }

private:
    EventCallbackList<T> mCallbackList;
};
#pragma warning(default: 4251)

template <typename T>
EventHandler<T>::EventHandler()
{
}

template <typename T>
EventHandler<T>::~EventHandler()
{
}

}
