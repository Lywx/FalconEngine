#pragma once

#include <FalconEngine/Graphics/Shaders/ShaderUniform.h>

namespace FalconEngine
{

template<typename T>
class ShaderUniformConstant : public ShaderUniformValue<T>
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using ShaderUniformValue<T>::ShaderUniformValue;
};

}
