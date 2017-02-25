#pragma once

#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniform.h>

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

template<typename T>
using ShaderUniformConstantSharedPtr = std::shared_ptr<ShaderUniformConstant<T>>;

template <typename T, typename ... Args>
ShaderUniformValueSharedPtr<T>
ShareConstant(Args&& ... args)
{
    return ShareUniform<T, ShaderUniformConstant<T>>(args ...);
}

}
