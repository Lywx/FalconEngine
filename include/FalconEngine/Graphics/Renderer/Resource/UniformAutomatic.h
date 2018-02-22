#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
#include <utility>

namespace FalconEngine
{

FALCON_ENGINE_PROGMA_BEGIN
template <typename T>
class UniformAutomatic : public UniformValue<T>
{
public:
    using ValueType = T;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using UniformValue<T>::UniformValue;
    UniformAutomatic(const std::string& name, UniformUpdateFunction<T>  updateFunction);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    UniformUpdateFunction<T>
    GetUpdateFunction() const;

    // @summary The function you would pass as a customized way to update the
    // uniform variable, mostly as a throw-away function that could not be reused.
    void
    SetUpdateFunction(UniformUpdateFunction<T> updateFunction);

    // @summry The function update the uniform variable optionally using update
    // function. If you intent to enforce reusability, you could override this
    // method using a fixed template class argument.
    virtual void
    UpdateInternal(const Camera *camera, const Visual *visual) override;

protected:
    UniformUpdateFunction<T> mUpdateFunction;
};
FALCON_ENGINE_PROGMA_END

template <typename T>
UniformAutomatic<T>::UniformAutomatic(const std::string& name, UniformUpdateFunction<T> updateFunction) :
    UniformValue<T>(name, T()),
    mUpdateFunction(std::move(updateFunction))
{
    // NOTE(Wuxiang): Automatic uniform is always being updated.
    this->mValueIsCurrent = false;
}

template <typename T>
UniformUpdateFunction<T>
UniformAutomatic<T>::GetUpdateFunction() const
{
    return mUpdateFunction;
}

template <typename T>
void
UniformAutomatic<T>::SetUpdateFunction(UniformUpdateFunction<T> updateFunction)
{
    mUpdateFunction = std::move(updateFunction);
}

template <typename T>
void
UniformAutomatic<T>::UpdateInternal(const Camera *camera, const Visual *visual)
{
    this->mValue = mUpdateFunction(visual, camera);
}

template<typename T>
using UniformAutomaticSp = std::shared_ptr<UniformAutomatic<T>>;

template <typename T, typename ... Args>
std::shared_ptr<UniformValue<T>>
                              ShareUniformAutomatic(const Args& ... args)
{
    return ShareUniform<T, UniformAutomatic<T>>(args ...);
}

}
