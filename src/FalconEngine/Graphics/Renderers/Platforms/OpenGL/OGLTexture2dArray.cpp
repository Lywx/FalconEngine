#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture2dArray.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(const std::vector<Texture2d *> textures) :
    mTexture(0),
    mTexturePrevious(0)
{
    if (textures.empty())
    {
        throw std::runtime_error("Texture array is empty.");
    }

    auto *texture = textures[0];
    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage[int(texture->mUsage)];

    // TODO(Wuxiang): Add mipmap support.
    // Allocate and setup buffer and dimension
    mBuffer.assign(textures.size(), 0);
    mDimension.assign(textures.size(), { 0, 0 });
    for (int i = 0; i < textures.size(); ++i)
    {
        mDimension[i][0] = textures[i]->mDimension[0];
        mDimension[i][1] = textures[i]->mDimension[1];
    }

    for (int i = 0; i < mDimension.size(); ++i)
    {
        glGenBuffers(1, &mBuffer[i]);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[i]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, textures[i]->mDataByteNum, nullptr, mUsage);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Allocate current texture memory
    glGenTextures(1, &mTexture);
    GLuint textureBindingPrevious = BindTexture(TextureType::Texture2dArray, mTexture);
    for (int i = 0; i < mDimension.size(); ++i)
    {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i,
                        mDimension[i][0], mDimension[i][1], 1,
                        mFormat, mType, nullptr);
    }

    // Restore previous texture binding
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureBindingPrevious);

    // Fill in the texture data
    for (int i = 0; i < mDimension.size(); ++i)
    {
        void *data = Map(i, 0, BufferAccessMode::Write);
        memcpy(data, textures[i]->mData, textures[i]->mDataByteNum);
        Unmap(i, 0);
    }
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
    for (int i = 0; i < mDimension.size(); ++i)
    {
        glDeleteBuffers(1, &mBuffer[i]);
    }

    glDeleteTextures(1, &mTexture);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture2dArray::Enable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTexturePrevious = BindTexture(TextureType::Texture2dArray, mTexture);
}

void
PlatformTexture2dArray::Disable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, mTexturePrevious);
}

void *
PlatformTexture2dArray::Map(int arrayIndex, int mipmapLevel, BufferAccessMode mode)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[arrayIndex]);
    void *pointer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return pointer;
}

void
PlatformTexture2dArray::Unmap(int arrayIndex, int mipmapLevel)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[arrayIndex]);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}

