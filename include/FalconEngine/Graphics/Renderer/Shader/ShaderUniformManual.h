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
    void
    SetValue(T value);
};

template <typename T>
void
ShaderUniformManual<T>::SetValue(T value)
{
    this->mValue = value;
    this->mUpdated = true;
}

template<typename T>
using ShaderUniformManualSharedPtr = std::shared_ptr<ShaderUniformManual<T>>;

template <typename T, typename ... Args>
std::shared_ptr<ShaderUniformValue<T>> ShareManual(const Args& ... args)
{
    return ShareUniform<T, ShaderUniformManual<T>>(args ...);
}

}
