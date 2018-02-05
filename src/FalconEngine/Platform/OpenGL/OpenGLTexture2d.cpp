#include <FalconEngine/Platform/OpenGL/OpenGLTexture2d.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>
#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2d::PlatformTexture2d(Renderer *renderer, const Texture2d *texture) :
    PlatformTexture(renderer, texture)
{
    // Bind newly created texture
    GLuint textureBindingPrevious = BindTexture(mTexturePtr->mType, mTextureObj);

    {
        glTexStorage2D(GL_TEXTURE_2D, 1, mFormatInternal, mDimension[0],
                       mDimension[1]);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);

        {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mDimension[0], mDimension[1],
                            mFormat, mType, nullptr);
        }

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Restore previous texture binding
    BindTexture(mTexturePtr->mType, textureBindingPrevious);
}

PlatformTexture2d::~PlatformTexture2d()
{
}

}

#endif