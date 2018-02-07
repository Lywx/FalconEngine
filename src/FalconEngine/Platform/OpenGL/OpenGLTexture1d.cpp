#include <FalconEngine/Platform/OpenGL/OpenGLTexture1d.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1d::PlatformTexture1d(Renderer *renderer, const Texture1d *texture) :
    PlatformTexture(renderer, texture)
{
    AllocateTexture();
}

PlatformTexture1d::~PlatformTexture1d()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture1d::AllocateTexture()
{
    // Bind newly created texture
    GLuint textureBindingPrevious = BindTexture(mTexturePtr->mType, mTextureObj);

    {
        glTexStorage1D(GL_TEXTURE_1D, 1, mFormatInternal, mDimension[0]);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);

        {
            glTexSubImage1D(GL_TEXTURE_1D, 0, 0, mDimension[0], mFormat, mType, nullptr);
        }

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Restore previous texture binding
    BindTexture(mTexturePtr->mType, textureBindingPrevious);
}

}

#endif