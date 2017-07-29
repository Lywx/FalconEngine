#pragma once

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
template <typename T>
class ShaderUniformAutomatic : public ShaderUniformValue<T>
{
public:
    using ValueType = T;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using ShaderUniformValue<T>::ShaderUniformValue;
    ShaderUniformAutomatic(const std::string& name, const ShaderUniformUpdateFunction<T> updateFunction);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Whether the uniform is enabled.
    bool
    IsUpdateEnabled() const;

    ShaderUniformUpdateFunction<T>
    GetUpdateFunction() const;

    // @summary The function you would pass as a customized way to update the
    // uniform variable, mostly as a throw-away function that could not be reused.
    void
    SetUpdateFunction(ShaderUniformUpdateFunction<T> updateFunction);

    // @summry The function update the uniform variable optionally using update
    // function. If you intent to enforce reusability, you could override this
    // method using a fixed template class argument.
    virtual void
    Update(const Camera *camera, const Visual *visual) override;

protected:
    ShaderUniformUpdateFunction<T> mUpdateFunction;
};

template <typename T>
ShaderUniformAutomatic<T>::ShaderUniformAutomatic(const std::string& name, const ShaderUniformUpdateFunction<T> updateFunction) :
    ShaderUniformValue<T>(name, T()),
    mUpdateFunction(updateFunction)
{
    this->mValueIsCurrent = false;
}

template <typename T>
bool
ShaderUniformAutomatic<T>::IsUpdateEnabled() const
{
    return mUpdateFunction != nullptr;
}

template <typename T>
ShaderUniformUpdateFunction<T>
ShaderUniformAutomatic<T>::GetUpdateFunction() const
{
    return mUpdateFunction;
}
#pragma warning(default: 4251)

template <typename T>
void
ShaderUniformAutomatic<T>::SetUpdateFunction(ShaderUniformUpdateFunction<T> updateFunction)
{
    mUpdateFunction = updateFunction;
}

template <typename T>
void
ShaderUniformAutomatic<T>::Update(const Camera *camera, const Visual *visual)
{
    if (mUpdateFunction)
    {
        this->mValue = mUpdateFunction(visual, camera);

        // NOTE(Wuxiang): Automatic uniform is always being updated.
        this->mValueIsCurrent = false;
    }
}

template<typename T>
using ShaderUniformAutomaticSp = std::shared_ptr<ShaderUniformAutomatic<T>>;

template <typename T, typename ... Args>
std::shared_ptr<ShaderUniformValue<T>>
                                    ShareAutomatic(const Args& ... args)
{
    return ShareUniform<T, ShaderUniformAutomatic<T>>(args ...);
}

}
