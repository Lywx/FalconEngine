#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTextureArray.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureArray.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTextureArray::PlatformTextureArray(const TextureArray *textureArray) :
    mTextureArrayObj(0),
    mTextureArrayObjPrevious(0),
    mTextureArrayPtr(textureArray),
    mFormatInternal(0),
    mFormat(0),
    mType(0),
    mUsage(0)
{
    mType = OpenGLTextureType[int(mTextureArrayPtr->mFormat)];
    mFormat = OpenGLTextureFormat[int(mTextureArrayPtr->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(mTextureArrayPtr->mFormat)];
    mUsage = OpenGLBufferUsage[int(mTextureArrayPtr->mUsage)];

    // Initialize dimension list.
    mDimension = mTextureArrayPtr->mDimension;

    // Initialize buffer object list.
    mBufferObjList.assign(mDimension[2], 0);

    // Allocate and setup buffer and dimension.
    glGenBuffers(mDimension[2], mBufferObjList.data());
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTextureArrayPtr->GetTextureSlice(textureIndex);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Fill in the texture data
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTextureArrayPtr->GetTextureSlice(textureIndex);
        auto textureData = Map(textureIndex,
                               BufferAccessMode::WriteBuffer,
                               BufferFlushMode::Automatic,
                               BufferSynchronizationMode::Unsynchronized, 0,
                               texture->mDataSize);
        memcpy(textureData, texture->mData, texture->mDataSize);
        Unmap(textureIndex);
    }

    // Generate texture object.
    glGenTextures(1, &mTextureArrayObj);

    // NOTE(Wuxiang): Derived texture class should only bind specific texture type
    // and allocate texture storage.

    // NEW(Wuxiang): Add mipmap support.
}

PlatformTextureArray::~PlatformTextureArray()
{
    glDeleteBuffers(mDimension[2], mBufferObjList.data());
    glDeleteTextures(1, &mTextureArrayObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTextureArray::Enable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTextureArrayObjPrevious = BindTexture(mTextureArrayPtr->mType, mTextureArrayObj);
}

void
PlatformTextureArray::Disable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture(mTextureArrayPtr->mType, mTextureArrayObjPrevious);
}

void *
PlatformTextureArray::Map(int                       textureIndex,
                          BufferAccessMode          access,
                          BufferFlushMode           flush,
                          BufferSynchronizationMode synchronization,
                          int64_t                   offset,
                          int64_t                   size)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    void *data = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, offset, size,
                                  OpenGLBufferAccessModeMark[int(access)] |
                                  OpenGLBufferFlushModeMark[int(flush)] |
                                  OpenGLBufferSynchronizationModeMark[int(synchronization)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return data;
}

void
PlatformTextureArray::Unmap(int textureIndex)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}
