#include <FalconEngine/Graphics/Renderer/Platforms/OpenGL/OGLTexture2d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2d::PlatformTexture2d(const Texture2d *texture) :
    mTexture(0),
    mTexturePrevious(0)
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
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataByteNum, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Allocate current texture memory
    glGenTextures(1, &mTexture);
    {
        // Bind newly created texture
        GLuint textureBindingPrevious = BindTexture(TextureType::Texture2d, mTexture);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mDimension[0], mDimension[1],
                        mFormat, mType, nullptr);

        // Restore previous texture binding
        glBindTexture(GL_TEXTURE_2D, textureBindingPrevious);
    }

    // Fill in the texture data
    void *textureData = Map(0, BufferAccessMode::Write);
    memcpy(textureData, texture->mData, texture->mDataByteNum);
    Unmap(0);
}

PlatformTexture2d::~PlatformTexture2d()
{
    // TODO(Wuxiang): Add mipmap support.
    glDeleteBuffers(1, &mBuffer);
    glDeleteTextures(1, &mTexture);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture2d::Enable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTexturePrevious = BindTexture(TextureType::Texture2d, mTexture);
}

void
PlatformTexture2d::Disable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, mTexturePrevious);
}

void *
PlatformTexture2d::Map(int mipmapLevel, BufferAccessMode mode)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    void *pointer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return pointer;
}

void
PlatformTexture2d::Unmap(int mipmapLevel)
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}
