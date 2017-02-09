#pragma once

#include <new>
#include <set>
#include <stack>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace FalconEngine
{

// NOTE(Wuxiang): Learned form handmade hero. To use this, you need to allocate
// memory storage first.
struct MemoryPool
{
    int64_t mStorageSize;
    void   *mStorage;
};

// NOTE(Wuxiang): Leaned from http://stackoverflow.com/questions/16378306/c11-memory-pool-design-pattern
class AutoReleaseObject
{
public:
    AutoReleaseObject();
    virtual ~AutoReleaseObject();
};

class AutoReleasePool final
{
public:
    static AutoReleasePool &Instance();

    AutoReleasePool();
    AutoReleasePool(const AutoReleasePool &) = delete;
    AutoReleasePool &operator = (const AutoReleasePool &) = delete;
    ~AutoReleasePool() noexcept;

    void
    Insert(AutoReleaseObject *object);

    void
    Erase(AutoReleaseObject *object);

private:

    // Won't allow users to create pool not on stack that easily. But it won't
    // make it totally impossible.
    void *operator new(size_t size);

    struct PrivateTraits
    {

    };

    struct Stack final : std::stack<AutoReleasePool *>
    {
        Stack()
        {
            std::unique_ptr<AutoReleasePool> pool(new AutoReleasePool(PrivateTraits()));
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

    AutoReleasePool(const PrivateTraits &);

    std::set<AutoReleaseObject *> mObjects;
};

}
