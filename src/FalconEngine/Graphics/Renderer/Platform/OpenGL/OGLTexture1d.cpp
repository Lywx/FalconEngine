#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture1d.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1d::PlatformTexture1d(const Texture1d *texture) :
    PlatformTexture(texture)
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

PlatformTexture1d::~PlatformTexture1d()
{
}

}

