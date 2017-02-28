#pragma once

#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniform.h>

namespace FalconEngine
{

template <typename T>
class ShaderUniformManual : public ShaderUniformValue<T>
{
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
    mValue = value;
    mUpdated = true;
}

template<typename T>
using ShaderUniformManualSharedPtr = std::shared_ptr<ShaderUniformManual<T>>;

template <typename T, typename ... Args>
ShaderUniformValueSharedPtr <
T > ShareManual(const Args& ... args)
{
    return ShareUniform<T, ShaderUniformManual<T>>(args ...);
}

}
