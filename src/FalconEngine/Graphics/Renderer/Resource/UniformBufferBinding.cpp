#include <FalconEngine/Graphics/Renderer/Resource/UniformBufferBinding.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
UniformBufferBinding::UniformBufferBinding() :
    mBindingIndex(),
    mBlockIndex(),
    mEnabled(true),
    mInitialized(false),
    mShaderMask(0)
{
}

UniformBufferBinding::UniformBufferBinding(
    std::shared_ptr<UniformBuffer> uniformBuffer,
    unsigned int shaderMask) :
    mBindingIndex(),
    mBlockIndex(),
    mEnabled(true),
    mInitialized(false),
    mShaderMask(shaderMask),
    mBuffer(std::move(uniformBuffer))
{
}

const UniformBuffer *
UniformBufferBinding::GetBuffer() const
{
    return mBuffer.get();
}

UniformBuffer *
UniformBufferBinding::GetBuffer()
{
    return mBuffer.get();
}

const std::string&
UniformBufferBinding::GetName() const
{
    return mBuffer->mName;
}

}
