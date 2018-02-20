#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>

namespace FalconEngine
{

// @remark Constant uniform's use is quite limited. Because it only updates once
// per shader during entire rendering process.
template<typename T>
class FALCON_ENGINE_API UniformConstant : public UniformValue<T>
{
public:
    using ValueType = T;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using UniformValue<T>::UniformValue;
};

template<typename T>
using UniformConstantSp = std::shared_ptr<UniformConstant<T>>;

template <typename T, typename ... Args>
std::shared_ptr<UniformValue<T>>
                              ShareUniformConstant(Args&& ... args)
{
    return ShareUniform<T, UniformConstant<T>>(args ...);
}

}
