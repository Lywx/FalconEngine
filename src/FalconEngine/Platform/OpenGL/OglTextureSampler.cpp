#include <FalconEngine/Platform/OpenGL/OglTextureSampler.h>
#include <FalconEngine/Platform/OpenGL/OglUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformSampler::PlatformSampler(const Sampler *sampler) :
    mSamplerPrevious(0)
{
    // NEW(Wuxiang): Add support for GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC
    glGenSamplers(1, &mSampler);
    glSamplerParameteri(mSampler, GL_TEXTURE_MIN_FILTER,
                        OpenGLSamplerFilterMode[int(sampler->mMinificationFilter)]);

    glSamplerParameteri(mSampler, GL_TEXTURE_MAG_FILTER,
                        OpenGLSamplerFilterMode[int(sampler->mMagnificationFilter)]);

    glSamplerParameteri(mSampler, GL_TEXTURE_WRAP_S,
                        OpenGLSamplerWrapMode[int(sampler->mWrapS)]);

    glSamplerParameteri(mSampler, GL_TEXTURE_WRAP_T,
                        OpenGLSamplerWrapMode[int(sampler->mWrapT)]);

    glSamplerParameteri(mSampler, GL_TEXTURE_WRAP_R,
                        OpenGLSamplerWrapMode[int(sampler->mWrapR)]);
}

PlatformSampler::~PlatformSampler()
{
    glDeleteSamplers(1, &mSampler);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformSampler::Enable(int textureUnit)
{
    mSamplerPrevious = BindSampler(textureUnit, mSampler);
}

void
PlatformSampler::Disable(int textureUnit)
{
    glBindSampler(textureUnit, mSamplerPrevious);
}

}
