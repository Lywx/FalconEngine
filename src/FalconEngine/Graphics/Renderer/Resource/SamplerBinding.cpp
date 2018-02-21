#include <FalconEngine/Graphics/Renderer/Resource/SamplerBinding.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
SamplerBinding::SamplerBinding():
    mSampler(nullptr),
    mSamplerShaderMask(0)
{
}

SamplerBinding::SamplerBinding(const Sampler *sampler, unsigned shaderMask):
    mSampler(sampler),
    mSamplerShaderMask(shaderMask)
{
}

}
