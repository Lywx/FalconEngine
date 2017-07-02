#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture2d.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2d::PlatformTexture2d(const Texture2d *texture) :
    PlatformTexture(texture),
    mTextureObj(0),
    mTextureObjPrevious(0)
{
    mDimension[0] = texture->mDimension[0];
    mDimension[1] = texture->mDimension[1];

    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage[int(texture->mUsage)];

    // TODO(Wuxiang): Add mipmap support.
    // int mipmapLevel = texture->mMipmapLevel;

    // Allocate current texture buffer
    glGenBuffers(1, &mBufferObj);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Fill in the texture data
    void *textureData = Map(0, BufferAccessMode::Write);
    memcpy(textureData, texture->mData, texture->mDataSize);
    Unmap(0);

    // Allocate current texture memory
    glGenTextures(1, &mTextureObj);
    {
        // Bind newly created texture
        GLuint textureBindingPrevious = BindTexture(texture->mType, mTextureObj);
        glTexStorage2D(GL_TEXTURE_2D, 1, mFormatInternal, mDimension[0], mDimension[1]);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mDimension[0], mDimension[1],
                        mFormat, mType, nullptr);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        // Restore previous texture binding
        glBindTexture(GL_TEXTURE_2D, textureBindingPrevious);
    }
}

PlatformTexture2d::~PlatformTexture2d()
{
    // TODO(Wuxiang): Add mipmap support.
    glDeleteBuffers(1, &mBufferObj);
    glDeleteTextures(1, &mTextureObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void *
PlatformTexture2d::Map(int /* mipmapLevel */, BufferAccessMode mode)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    void *data = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return data;
}

void
PlatformTexture2d::Unmap(int /* mipmapLevel */)
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}
