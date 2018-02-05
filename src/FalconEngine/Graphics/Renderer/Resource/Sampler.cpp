#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Sampler::Sampler() :
    // @ref https://www.opengl.org/sdk/docs/man/html/glSamplerParameter.xhtml
    mMagnificationFilter(SamplerMagnificationFilter::Linear),
    mMinificationFilter(SamplerMinificationFilter::Linear),
    mMipmapEnabled(false),
    mMipmapFilter(SamplerMipmapFilter::Linear),
    mWrapS(SamplerWrapMode::Repeat),
    mWrapT(SamplerWrapMode::Repeat),
    mWrapR(SamplerWrapMode::Repeat)
{
}

Sampler::Sampler(SamplerMagnificationFilter magnificationFilter,
                 SamplerMinificationFilter minificationFilter,
                 SamplerMipmapFilter mipmapFilter,
                 SamplerWrapMode wrapS,
                 SamplerWrapMode wrapT,
                 SamplerWrapMode wrapR) :
    mMagnificationFilter(magnificationFilter),
    mMinificationFilter(minificationFilter),
    mMipmapEnabled(false),
    mMipmapFilter(mipmapFilter),
    mWrapS(wrapS),
    mWrapT(wrapT),
    mWrapR(wrapR)
{
}

Sampler::~Sampler()
{
    FALCON_ENGINE_RENDERER_UNBIND(this);
}

}
