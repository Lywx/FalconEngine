#pragma once

#include <FalconEngine/Graphics/Shaders/ShaderUniform.h>

namespace FalconEngine
{

template <typename T>
class ShaderUniformManual : public ShaderUniformValue<T>
{
    FALCON_ENGINE_RTTI_DECLARE;

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
void ShaderUniformManual<T>::SetValue(T value)
{
    mValue = value;
    mUpdated = true;
}

}
