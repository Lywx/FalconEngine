#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <string>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class Camera;
class Visual;

FALCON_ENGINE_CLASS_BEGIN UniformBuffer :
public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UniformBuffer(const std::string & name, size_t storageSize);
    virtual ~UniformBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @remark If the value is not current, renderer would call Update member
    // function for this instance of uniform.
    bool
    IsUpdateNeeded() const;

    void
    Update(const Camera * camera, const Visual * visual);

protected:
    bool mValueIsCurrent;
};
FALCON_ENGINE_CLASS_END

template <typename T>
using ShaderUniformBufferUpdatePrototype = void(const Visual *, const Camera *, T *);

template <typename T>
using ShaderUniformBufferUpdateFunction = std::function<ShaderUniformBufferUpdatePrototype<T>>;

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class UniformBufferValue : public UniformBuffer
{
public:
    UniformBufferValue(const std::string & name,
                       size_t storageSize,
                       const ShaderUniformBufferUpdateFunction<T>& updateFunction);

public:
protected:
    ShaderUniformBufferUpdateFunction<T> mUpdateFunction;
};
FALCON_ENGINE_PROGMA_END

template <typename T>
UniformBufferValue<T>::UniformBufferValue(
    const std::string& name,
    size_t storageSize,
    const ShaderUniformBufferUpdateFunction<T>& updateFunction) :
    UniformBuffer(name, storageSize),
    mUpdateFunction(updateFunction)
{
}

}
