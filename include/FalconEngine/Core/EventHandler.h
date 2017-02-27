#pragma once

#include <FalconEngine/Core/CoreInclude.h>

#include <functional>
#include <list>

namespace FalconEngine
{

template <typename T>
using EventCallback = std::function<void(void *, T)>;

template <typename T>
using EventCallbackList = std::list<EventCallback<T>>;

// @ref Luis Sempe User Interface Programming for Games, 2014.
template <typename T>
class EventHandler
{
public:
    EventHandler();
    virtual ~EventHandler();

    typename EventCallbackList<T>::iterator
    operator += (EventCallback<T> callback)
    {
        mCallbackList.emplace_front(callback);
        return mCallbackList.begin();
    }

    void
    operator -= (typename EventCallbackList<T>::iterator& it)
    {
        mCallbackList.erase(it);
    }

    void
    Invoke(void *sender, T data)
    {
        for (auto& callback : mCallbackList)
        {
            callback(sender, data);
        }
    }

private:
    EventCallbackList<T> mCallbackList;
};

template <typename T>
EventHandler<T>::EventHandler()
{
}

template <typename T>
EventHandler<T>::~EventHandler()
{
}

}
