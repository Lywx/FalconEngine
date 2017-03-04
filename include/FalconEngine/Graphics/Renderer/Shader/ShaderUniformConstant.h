#pragma once

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

template<typename T>
class ShaderUniformConstant : public ShaderUniformValue<T>
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using ShaderUniformValue<T>::ShaderUniformValue;
};

template<typename T>
using ShaderUniformConstantSharedPtr = std::shared_ptr<ShaderUniformConstant<T>>;

template <typename T, typename ... Args>
ShaderUniformValueSharedPtr<T>
ShareConstant(Args&& ... args)
{
    return ShareUniform<T, ShaderUniformConstant<T>>(args ...);
}

}