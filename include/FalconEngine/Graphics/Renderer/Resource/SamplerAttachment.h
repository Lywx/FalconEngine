#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{
class Sampler;

FALCON_ENGINE_CLASS_BEGIN SamplerAttachment final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    SamplerAttachment();
    SamplerAttachment(const Sampler * sampler, unsigned int shaderMask);
    ~SamplerAttachment() = default;

public:
    const Sampler *mSampler;
    unsigned int mSamplerShaderMask;
};
FALCON_ENGINE_CLASS_END

}
