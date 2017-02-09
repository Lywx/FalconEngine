#include <FalconEngine/Core/MemoryPool.h>

namespace FalconEngine
{

AutoReleaseObject::AutoReleaseObject()
{
    AutoReleasePool::Instance().Insert(this);
}

AutoReleaseObject::~AutoReleaseObject()
{
    AutoReleasePool::Instance().Erase(this);
}

AutoReleasePool& AutoReleasePool::Instance()
{
    assert(!AutoReleasePoolStack.empty());
    return *AutoReleasePoolStack.top();
}

thread_local AutoReleasePool::Stack AutoReleasePool::AutoReleasePoolStack;

AutoReleasePool::AutoReleasePool()
{
    AutoReleasePoolStack.emplace(this);
}

AutoReleasePool::~AutoReleasePool() noexcept
{
    std::set<AutoReleaseObject *> objects;
    objects.swap(mObjects);

    // Release current pool
    for (auto *object : objects)
    {
        delete object;
    }

    // Restore previous pool
    AutoReleasePoolStack.pop();
}

AutoReleasePool::AutoReleasePool(const PrivateTraits&)
{
}

void
AutoReleasePool::Insert(AutoReleaseObject *object)
{
    mObjects.insert(object);
}

void
AutoReleasePool::Erase(AutoReleaseObject *object)
{
    mObjects.erase(object);
}

void *
AutoReleasePool::operator new(size_t size)
{
    return ::operator new(size);
}

}
