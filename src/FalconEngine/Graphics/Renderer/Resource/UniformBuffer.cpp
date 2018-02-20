#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
UniformBuffer::UniformBuffer(const std::string & name,
                             size_t storageSize,
                             ResourceStorageMode storageMode) :
    Buffer(1,
           storageSize,
           BufferType::UniformBuffer,
           ResourceCreationAccessMode::GpuReadCpuWrite,
           ResourceCreationAccessUsage::Dynamic,
           storageMode),
    mEnabled(true),
    mInitialized(false),
    mValueIsCurrent(true)
{
    mName = name;
}

UniformBuffer::~UniformBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
UniformBuffer::IsUpdateNeeded() const
{
    return !mValueIsCurrent;
}

void
UniformBuffer::UpdateContext(const Camera *, const Visual *, void *)
{
    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
}
}
