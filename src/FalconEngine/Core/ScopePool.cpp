#include <FalconEngine/Core/ScopePool.h>

namespace FalconEngine
{

ScopeObject::ScopeObject()
{
    ScopePool::GetInstance().Insert(this);
}

ScopeObject::~ScopeObject()
{
    ScopePool::GetInstance().Erase(this);
}

ScopePool& ScopePool::GetInstance()
{
    assert(!AutoReleasePoolStack.empty());
    return *AutoReleasePoolStack.top();
}

thread_local ScopePool::Stack ScopePool::AutoReleasePoolStack;

ScopePool::ScopePool()
{
    AutoReleasePoolStack.emplace(this);
}

ScopePool::~ScopePool() noexcept
{
    std::set<ScopeObject *> objects;
    objects.swap(mObjects);

    // Release current pool
    for (auto *object : objects)
    {
        delete object;
    }

    // Restore previous pool
    AutoReleasePoolStack.pop();
}

ScopePool::ScopePool(const PrivateTraits&)
{
}

void
ScopePool::Insert(ScopeObject *object)
{
    mObjects.insert(object);
}

void
ScopePool::Erase(ScopeObject *object)
{
    mObjects.erase(object);
}

void *
ScopePool::operator new(size_t size)
{
    return ::operator new(size);
}

}
