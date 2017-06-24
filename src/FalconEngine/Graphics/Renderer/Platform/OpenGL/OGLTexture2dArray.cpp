#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture2dArray.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(const Texture2dArray *textureArray) :
    mTexture(0),
    mTexturePrevious(0)
{
    mType = OpenGLTextureType[int(textureArray->mFormat)];
    mFormat = OpenGLTextureFormat[int(textureArray->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(textureArray->mFormat)];
    mUsage = OpenGLBufferUsage[int(textureArray->mUsage)];

    // TODO(Wuxiang): Add mipmap support.
    // Allocate and setup buffer and dimension
    {
        mTextureArraySize = textureArray->mDimension[2];
        mBuffer.assign(mTextureArraySize, 0);
        mDimension.assign(mTextureArraySize, { 0, 0 });

        for (int textureIndex = 0; textureIndex < mTextureArraySize; ++textureIndex)
        {
            auto texture = textureArray->GetTextureSlice(textureIndex);
            mDimension[textureIndex][0] = texture->mDimension[0];
            mDimension[textureIndex][1] = texture->mDimension[1];
        }

        for (int textureIndex = 0; textureIndex < mTextureArraySize; ++textureIndex)
        {
            glGenBuffers(1, &mBuffer[textureIndex]);
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[textureIndex]);
            glBufferData(GL_PIXEL_UNPACK_BUFFER, textureArray->GetTextureSlice(textureIndex)->mDataByteNum, nullptr, mUsage);
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        }

        // NOTE(Wuxiang): mBuffer, mDimension vector size is relatively small. Don't
        // worry about the overflowing.
        assert(mTextureArraySize == int(mBuffer.size()));
        assert(mTextureArraySize == int(mDimension.size()));
    }

    // Fill in the texture data
    for (int textureIndex = 0; textureIndex < mTextureArraySize; ++textureIndex)
    {
        auto texture = textureArray->GetTextureSlice(textureIndex);
        void *textureData = Map(textureIndex, 0, BufferAccessMode::Write);
        memcpy(textureData, texture->mData, texture->mDataByteNum);
        Unmap(textureIndex, 0);
    }

    // Allocate current texture memory
    glGenTextures(1, &mTexture);
    {
        GLuint textureBindingPrevious = BindTexture(TextureType::Texture2dArray, mTexture);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, mFormatInternal, textureArray->mDimension[0], textureArray->mDimension[1], textureArray->mDimension[2]);

        // Bind newly created texture
        for (int textureIndex = 0; textureIndex < mTextureArraySize; ++textureIndex)
        {
            // Bind PBO to provide asynchronous copy of texture data.
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[textureIndex]);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, textureIndex,
                            mDimension[textureIndex][0], mDimension[textureIndex][1], 1,
                            mFormat, mType, nullptr);
        }

        // Unbind the PBO.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        // Restore previous texture binding
        glBindTexture(GL_TEXTURE_2D_ARRAY, textureBindingPrevious);
    }
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
    for (int i = 0; i < mTextureArraySize; ++i)
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
PlatformTexture2dArray::Map(int arrayIndex, int /* mipmapLevel */, BufferAccessMode mode)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[arrayIndex]);
    void *pointer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, OpenGLBufferAccessMode[int(mode)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return pointer;
}

void
PlatformTexture2dArray::Unmap(int arrayIndex, int /* mipmapLevel */)
{
    // TODO(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBuffer[arrayIndex]);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}

