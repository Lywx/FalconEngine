#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>

namespace FalconEngine
{

template <typename T>
class UniformManual : public UniformValue<T>
{
public:
    using ValueType = T;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using UniformValue<T>::UniformValue;

public:
    virtual void
    SetValue(const T& value) override;
};

template <typename T>
void
UniformManual<T>::SetValue(const T& value)
{
    this->mValue = value;
    this->mValueIsCurrent = true;
}

template <typename T, typename ... Args>
std::shared_ptr<UniformValue<T>>
                              ShareUniformManual(const Args& ... args)
{
    return ShareUniform<T, UniformManual<T>>(args ...);
}

}
