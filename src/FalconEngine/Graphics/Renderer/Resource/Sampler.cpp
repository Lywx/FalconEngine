#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Sampler::Sampler() :
    // @ref https://www.opengl.org/sdk/docs/man/html/glSamplerParameter.xhtml
    mMinificationFilter(SamplerMinificationFilter::LinearMipmapLinear),
    mMagnificationFilter(SamplerMagnificationFilter::Linear),
    mWrapS(SamplerWrapMode::Repeat),
    mWrapT(SamplerWrapMode::Repeat),
    mWrapR(SamplerWrapMode::Repeat)
{
}

Sampler::Sampler(SamplerMinificationFilter minificationFilter,
                 SamplerMagnificationFilter magnificationFilter,
                 SamplerWrapMode wrapS,
                 SamplerWrapMode wrapT,
                 SamplerWrapMode wrapR) :
    mMinificationFilter(minificationFilter),
    mMagnificationFilter(magnificationFilter),
    mWrapS(wrapS),
    mWrapT(wrapT),
    mWrapR(wrapR)
{
}

Sampler::~Sampler()
{
}

}
