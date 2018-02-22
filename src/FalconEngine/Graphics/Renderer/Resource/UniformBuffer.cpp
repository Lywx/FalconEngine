#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

#include <utility>

#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
UniformBuffer::UniformBuffer(std::string name,
                             size_t storageSize,
                             ResourceStorageMode storageMode) :
    Buffer(1,
           storageSize,
           BufferType::UniformBuffer,
           ResourceCreationAccessMode::GpuReadCpuWrite,
           ResourceCreationAccessUsage::Dynamic,
           storageMode),
    mName(std::move(name)),
    mDataIsCurrent(true)
{
}

UniformBuffer::~UniformBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
UniformBuffer::ShouldUpdateContext() const
{
    return !mDataIsCurrent;
}

void
UniformBuffer::UpdateContextInternal(const Camera *, const Visual *, void *)
{
    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
}
}
