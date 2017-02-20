#pragma once

#include <FalconEngine/Core/CoreInclude.h>

#include <new>
#include <set>
#include <stack>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace FalconEngine
{

// NOTE(Wuxiang): Leaned from http://stackoverflow.com/questions/16378306/c11-memory-pool-design-pattern
class ScopeObject
{
public:
    ScopeObject();
    virtual ~ScopeObject();
};

class ScopePool final
{
public:
    static ScopePool &GetInstance();

    ScopePool();
    ScopePool(const ScopePool &) = delete;
    ScopePool &operator = (const ScopePool &) = delete;
    ~ScopePool() noexcept;

    void
    Insert(ScopeObject *object);

    void
    Erase(ScopeObject *object);

private:

    // Won't allow users to create pool not on stack that easily. But it won't
    // make it totally impossible.
    void *operator new(size_t size);

    struct PrivateTraits
    {

    };

    struct Stack final : std::stack<ScopePool *>
    {
        Stack()
        {
            std::unique_ptr<ScopePool> pool(new ScopePool(PrivateTraits()));
            push(pool.get());
            pool.release();
        }

        ~Stack()
        {
            assert(!AutoReleasePoolStack.empty());
            delete AutoReleasePoolStack.top();
        }
    };

    static thread_local Stack AutoReleasePoolStack;

    ScopePool(const PrivateTraits &);

    std::set<ScopeObject *> mObjects;
};

}
