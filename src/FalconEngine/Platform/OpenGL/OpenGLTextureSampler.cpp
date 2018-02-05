#include <FalconEngine/Platform/OpenGL/OpenGLTextureSampler.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformSampler::PlatformSampler(Renderer *, const Sampler *sampler) :
    mSamplerObj(0),
    mSamplerObjPrevious(0),
    mSamplerPtr(sampler)
{
    Create();
}

PlatformSampler::~PlatformSampler()
{
    glDeleteSamplers(1, &mSamplerObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformSampler::Enable(Renderer *, int textureUnit)
{
    mSamplerObjPrevious = BindSampler(textureUnit, mSamplerObj);
}

void
PlatformSampler::Disable(Renderer *, int textureUnit)
{
    glBindSampler(textureUnit, mSamplerObjPrevious);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformSampler::Create()
{
    // NEW(Wuxiang): Add support for GL_TEXTURE_BORDER_COLOR, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD, GL_TEXTURE_LOD_BIAS, GL_TEXTURE_COMPARE_MODE, GL_TEXTURE_COMPARE_FUNC
    glGenSamplers(1, &mSamplerObj);

    auto magFilter = mSamplerPtr->mMagnificationFilter;
    auto minFilter = mSamplerPtr->mMinificationFilter;
    auto mipmapFilter = mSamplerPtr->mMipmapFilter;

    // Magnification
    glSamplerParameteri(mSamplerObj, GL_TEXTURE_MAG_FILTER,
                        OpenGLSamplerFilterMode[int(magFilter)]);

    // Mipmap and minification
    if (mSamplerPtr->mMipmapEnabled)
    {
        int mipmapModeIndex = 0;
        if (minFilter == SamplerMinificationFilter::Linear)
        {
            mipmapModeIndex += 2;
        }
        if (mipmapFilter == SamplerMipmapFilter::Linear)
        {
            mipmapModeIndex += 1;
        }

        glSamplerParameteri(mSamplerObj, GL_TEXTURE_MIN_FILTER,
                            OpenGLSamplerMipmapMode[mipmapModeIndex]);
    }
    else
    {
        glSamplerParameteri(mSamplerObj, GL_TEXTURE_MIN_FILTER,
                            OpenGLSamplerFilterMode[int(minFilter)]);
    }

    glSamplerParameteri(mSamplerObj, GL_TEXTURE_WRAP_S,
                        OpenGLSamplerWrapMode[int(mSamplerPtr->mWrapS)]);

    glSamplerParameteri(mSamplerObj, GL_TEXTURE_WRAP_T,
                        OpenGLSamplerWrapMode[int(mSamplerPtr->mWrapT)]);

    glSamplerParameteri(mSamplerObj, GL_TEXTURE_WRAP_R,
                        OpenGLSamplerWrapMode[int(mSamplerPtr->mWrapR)]);
}

}

#endif