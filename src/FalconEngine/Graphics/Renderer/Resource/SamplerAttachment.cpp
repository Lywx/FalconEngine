#include <FalconEngine/Graphics/Renderer/Resource/SamplerAttachment.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
SamplerAttachment::SamplerAttachment():
    mSampler(nullptr),
    mSamplerShaderMask(0)
{
}

SamplerAttachment::SamplerAttachment(const Sampler *sampler, unsigned shaderMask):
    mSampler(sampler),
    mSamplerShaderMask(shaderMask)
{
}

}
