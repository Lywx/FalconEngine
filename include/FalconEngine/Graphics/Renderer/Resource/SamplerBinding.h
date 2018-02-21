#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{
class Sampler;

FALCON_ENGINE_CLASS_BEGIN SamplerBinding final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    SamplerBinding();
    SamplerBinding(const Sampler * sampler, unsigned int shaderMask);
    ~SamplerBinding() = default;

public:
    const Sampler *mSampler;
    unsigned int mSamplerShaderMask;
};
FALCON_ENGINE_CLASS_END

}
