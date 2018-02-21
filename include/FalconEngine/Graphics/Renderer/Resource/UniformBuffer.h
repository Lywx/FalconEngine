#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN UniformBufferMetadata
{
public:
    UniformBufferMetadata(std::string name, size_t storageSize, int bindingIndex) :
        mBindingIndex(bindingIndex),
        mBlockIndex(-1),
        mCapacitySize(storageSize),
        mEnabled(true),
        mName(std::move(name))
    {
    }

public:
    // NOTE(Wuxiang): Used both in OpenGL and Direct3D.
    int mBindingIndex;

    // NOTE(Wuxiang): Specific to OpenGL.
    int mBlockIndex;

    size_t mCapacitySize;
    bool mEnabled;
    std::string mName;
};
FALCON_ENGINE_CLASS_END

class Camera;
class Visual;

FALCON_ENGINE_CLASS_BEGIN UniformBuffer :
public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UniformBuffer(const std::string & name, size_t storageSize, ResourceStorageMode storageMode);
    virtual ~UniformBuffer();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @remark If the value is not current, renderer would call Update member
    // function for this instance of uniform.
    bool
    IsUpdateNeeded() const;

    virtual void
    UpdateContext(const Camera * camera, const Visual * visual, void *data);

public:
    // Uniform Block name in OpenGL or Constant Buffer name in Direct3D.
    std::string mName;

protected:
    bool mValueIsCurrent;
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class UniformBufferTemplate : public UniformBuffer
{
public:
    using UniformBuffer::UniformBuffer;
};
FALCON_ENGINE_PROGMA_END

template <typename T, typename U, typename ... Args>
std::shared_ptr<UniformBufferTemplate<T>>
                                       ShareUniformBuffer(Args&& ... args)
{
    return std::static_pointer_cast<UniformBufferTemplate<T>>(
               std::make_shared<U>(args ...));
}

}

#define FALCON_ENGINE_UNIFORM_BUFFER_FUNC_BEGIN(captureList, DataKlass) \
    std::bind([captureList](const FalconEngine::Visual * visual, const FalconEngine::Camera *camera, DataKlass *data)

#define FALCON_ENGINE_UNIFORM_BUFFER_FUNC_END , std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

