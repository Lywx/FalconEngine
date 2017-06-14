#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture1d.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1d::PlatformTexture1d(const Texture1d *texture) :
    mTexture(0),
    mTexturePrevious(0)
{
    mDimension = texture->mDimension[0];

    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage[int(texture->mUsage)];

    // TODO(Wuxiang): Add mipmap support.
    // int mipmapLevel = texture->mMipmapLevel;

    // Allocate current texture buffer
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataByteNum, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Fill in the texture data
    void *textureData = Map(0, BufferAccessMode::Write);
    memcpy(textureData, texture->mData, texture->mDataByteNum);
    Unmap(0);

    // Allocate current texture memory
    glGenTextures(1, &mTexture);
    {
        // Bind newly created texture
        GLuint textureBindingPrevious = BindTexture(TextureType::Texture1d, mTexture);
        glTexStorage1D(GL_TEXTURE_1D, 1, mFormatInternal, mDimension);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 0, mDimension, mFormat, mType, nullptr);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        // Restore previous texture binding
        glBindTexture(GL_TEXTURE_1D, textureBindingPrevious);
    }
}

PlatformTexture1d::~PlatformTexture1d()
{
    // TODO(Wuxiang): Add mipmap support.
    glDeleteBuffers(1, &mBuffer);
    glDeleteTextures(1, &mTexture);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture1d::Enable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTexturePrevious = BindTexture(TextureType::Texture1d, mTexture);
}

void
PlatformTexture1d::Disable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_1D, mTexturePrevious);
}

void *
PlatformTexture1d::Map(int /* mipmapLevel */, BufferAccessMode mode)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    void *pointer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return pointer;
}

void
PlatformTexture1d::Unmap(int /* mipmapLevel */)
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}

