#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <string>

namespace FalconEngine
{
class UniformBuffer;

FALCON_ENGINE_CLASS_BEGIN UniformBufferBinding final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UniformBufferBinding();
    UniformBufferBinding(std::shared_ptr<UniformBuffer> uniformBuffer, unsigned int shaderMask);
    ~UniformBufferBinding() = default;

public:
    const UniformBuffer *
    GetBuffer() const;

    UniformBuffer *
    GetBuffer();

    const std::string&
    GetName() const;

public:
    // NOTE(Wuxiang): Only used in OpenGL for Uniform Block Buffer. The binding
    // point for Uniform Block Buffer.
    int mBindingIndex;

    // NOTE(Wuxiang): Only used in OpenGL for Uniform Block Buffer. The Uniform
    // Block index.
    int mBlockIndex;

    bool mEnabled;

    bool mInitialized;

    unsigned int mShaderMask;

private:
    std::shared_ptr<UniformBuffer> mBuffer;
};
FALCON_ENGINE_CLASS_END

}
