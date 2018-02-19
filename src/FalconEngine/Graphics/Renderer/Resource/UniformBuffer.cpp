#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
UniformBuffer::UniformBuffer(const std::string & name, size_t storageSize) :
    Buffer(1,
           storageSize,
           BufferType::UniformBuffer,
           ResourceCreationAccessMode::GpuReadCpuWrite,
           ResourceCreationAccessUsage::Dynamic,
           ResourceStorageMode::Device),
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
UniformBuffer::Update(const Camera *camera, const Visual *visual)
{
}
}
