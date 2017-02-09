#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>

namespace FalconEngine
{

TextureSampler::TextureSampler() :
    // @ref https://www.opengl.org/sdk/docs/man/html/glSamplerParameter.xhtml
    mMinificationFilter(SamplerMinificationFilter::LinearMipmapLinear),
    mMagnificationFilter(SamplerMagnificationFilter::Linear),
    mWrapS(SamplerWrapMode::Repeat),
    mWrapT(SamplerWrapMode::Repeat),
    mWrapR(SamplerWrapMode::Repeat)
{
}

TextureSampler::TextureSampler(SamplerMinificationFilter minificationFilter,
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

TextureSampler::~TextureSampler()
{
}

}
