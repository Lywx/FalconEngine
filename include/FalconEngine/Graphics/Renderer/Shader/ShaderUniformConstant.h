#pragma once

#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

template<typename T>
class FALCON_ENGINE_API ShaderUniformConstant : public ShaderUniformValue<T>
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
std::shared_ptr<ShaderUniformValue<T>>
ShareConstant(Args&& ... args)
{
    return ShareUniform<T, ShaderUniformConstant<T>>(args ...);
}

}
