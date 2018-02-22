#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <string>

#include <FalconEngine/Graphics/Renderer/Resource/UniformBuffer.h>

namespace FalconEngine
{

class Camera;
class Visual;

template <typename T>
using UniformBufferUpdatePrototype = void(const Visual *, const Camera *, T *);

template <typename T>
using UniformBufferUpdateFunction = std::function<UniformBufferUpdatePrototype<T>>;

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class UniformBufferAutomatic : public UniformBufferTemplate<T>
{
public:
    UniformBufferAutomatic(const std::string & name,
                           UniformBufferUpdateFunction<T> updateFunction);

public:
    virtual void
    UpdateContextInternal(const Camera *camera, const Visual *visual, void *data) override;

protected:
    virtual void
    Update(const Camera *camera, const Visual *visual, T *data);

protected:
    UniformBufferUpdateFunction<T> mUpdateFunction;
};
FALCON_ENGINE_PROGMA_END

template <typename T>
UniformBufferAutomatic<T>::UniformBufferAutomatic(
    const std::string& name,
    UniformBufferUpdateFunction<T> updateFunction) :
    UniformBufferTemplate<T>(name, sizeof(T), ResourceStorageMode::Device),
    mUpdateFunction(std::move(updateFunction))
{
    // NOTE(Wuxiang): Automatic uniform is always being updated.
    this->mValueIsCurrent = false;
}

template <typename T>
void
UniformBufferAutomatic<T>::UpdateContextInternal(const Camera *camera, const Visual *visual, void *data)
{
    Update(camera, visual, reinterpret_cast<T *>(data));
}

template <typename T>
void
UniformBufferAutomatic<T>::Update(const Camera *camera, const Visual *visual, T *data)
{
    mUpdateFunction(visual, camera, data);
}

template <typename T, typename ... Args>
std::shared_ptr<UniformBufferTemplate<T>>
                                       ShareUniformBufferAutomatic(const Args& ... args)
{
    return ShareUniformBuffer<T, UniformBufferAutomatic<T>>(args ...);
}

}
