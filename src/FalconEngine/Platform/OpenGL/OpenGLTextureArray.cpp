#include <FalconEngine/Platform/OpenGL/OpenGLTextureArray.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/TextureArray.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTextureArray::PlatformTextureArray(Renderer *renderer, const TextureArray *textureArray) :
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
    mUsage = OpenGLBufferUsage(mTextureArrayPtr->mAccessMode, mTextureArrayPtr->mAccessUsage);

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
        auto textureData = Map(renderer, textureIndex,
                               ResourceMapAccessMode::WriteBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized, 0,
                               texture->mDataSize);
        memcpy(textureData, texture->mData, texture->mDataSize);
        Unmap(renderer, textureIndex);
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
PlatformTextureArray::Enable(Renderer *, int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTextureArrayObjPrevious = BindTexture(mTextureArrayPtr->GetTextureType(), mTextureArrayObj);
}

void
PlatformTextureArray::Disable(Renderer *, int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture(mTextureArrayPtr->GetTextureType(), mTextureArrayObjPrevious);
}

void *
PlatformTextureArray::Map(Renderer *,
                          int textureIndex,
                          ResourceMapAccessMode access,
                          ResourceMapFlushMode flush,
                          ResourceMapSyncMode synchronization,
                          int64_t                   offset,
                          int64_t                   size)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    void *data = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, offset, size,
                                  OpenGLBufferAccessModeBit[int(access)] |
                                  OpenGLBufferFlushModeBit[int(flush)] |
                                  OpenGLBufferSynchronizationModeBit[int(synchronization)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return data;
}

void
PlatformTextureArray::Unmap(Renderer *, int textureIndex)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}

#endif