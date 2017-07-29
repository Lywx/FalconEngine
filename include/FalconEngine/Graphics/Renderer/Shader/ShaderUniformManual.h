#pragma once

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

template <typename T>
class ShaderUniformManual : public ShaderUniformValue<T>
{
public:
    using ValueType = T;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using ShaderUniformValue<T>::ShaderUniformValue;

public:
    virtual void
    SetValue(const T& value) override;
};

template <typename T>
void
ShaderUniformManual<T>::SetValue(const T& value)
{
    this->mValue = value;
    this->mValueIsCurrent = true;
}

template <typename T, typename ... Args>
std::shared_ptr<ShaderUniformValue<T>>
                                    ShareManual(const Args& ... args)
{
    return ShareUniform<T, ShaderUniformManual<T>>(args ...);
}

}
