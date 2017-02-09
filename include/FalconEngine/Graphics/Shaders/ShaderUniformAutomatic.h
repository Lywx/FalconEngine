#pragma once

#include <FalconEngine/Graphics/Shaders/ShaderUniform.h>

namespace FalconEngine
{

template <typename T>
class ShaderUniformAutomatic : public ShaderUniformValue<T>
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using ShaderUniformValue<T>::ShaderUniformValue;
    ShaderUniformAutomatic(const std::string& name, const ShaderUniformUpdateFunction updateFunction);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    // @summary Whether
    bool
    GetUpdateEnable() const;

    ShaderUniformUpdateFunction
    GetUpdateFunction() const;

    // @summary The function you would pass as a customized way to update the
    // uniform variable, mostly as a throw-away function that could not be reused.
    void
    SetUpdateFunction(ShaderUniformUpdateFunction updateFunction);

    // TODO(Wuxiang 2017-01-25 11:42): not done yet

    // @summry The function update the uniform variable optionally using update
    // function. If you intent to enforce reusability, you could override this
    // method using a fixed template class argument.
    virtual void
    Update(const Visual *visual, const Camera *camera);

protected:
    ShaderUniformUpdateFunction mUpdateFunction;
};

template <typename T>
ShaderUniformAutomatic<T>::ShaderUniformAutomatic(const std::string& name, const ShaderUniformUpdateFunction updateFunction) :
    ShaderUniformValue<T>(name, T()),
    mUpdateFunction(updateFunction)
{
}

template <typename T>
bool
ShaderUniformAutomatic<T>::GetUpdateEnable() const
{
    return mUpdateFunction != nullptr;
}

template <typename T>
ShaderUniformUpdateFunction
ShaderUniformAutomatic<T>::GetUpdateFunction() const
{
    return mUpdateFunction;
}

template <typename T>
void
ShaderUniformAutomatic<T>::SetUpdateFunction(ShaderUniformUpdateFunction updateFunction)
{
    mUpdateFunction = updateFunction;
}

template <typename T>
void
ShaderUniformAutomatic<T>::Update(const Visual *visual, const Camera *camera)
{
    if (mUpdateFunction)
    {
        mUpdateFunction(visual, camera);
    }
}

}
