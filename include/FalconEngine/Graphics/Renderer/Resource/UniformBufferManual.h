#pragma once

#include <FalconEngine/Core/Macro.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class UniformBufferManual : public UniformBufferTemplate<T>
{
public:
    explicit UniformBufferManual(const std::string& name) :
        UniformBufferTemplate<T>(name, sizeof(T), ResourceStorageMode::Host)
    {
    }

public:
    virtual void
    UpdateContextInternal(const Camera *camera, const Visual *visual, void *data) override;
};
FALCON_ENGINE_PROGMA_END

template <typename T>
void
UniformBufferManual<T>::UpdateContextInternal(const Camera *, const Visual *, void *data)
{
    std::memcpy(data, this->mData, this->mDataSize);

    this->mDataIsCurrent = true;
}

template <typename T, typename ... Args>
std::shared_ptr<UniformBufferTemplate<T>>
                                       ShareUniformBufferManual(const Args& ... args)
{
    return ShareUniformBuffer<T, UniformBufferManual<T>>(args ...);
}

}
