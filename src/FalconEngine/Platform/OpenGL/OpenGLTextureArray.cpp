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
    mTextureArrayPtr(textureArray),
    mTextureObj(0),
    mTextureObjPrevious(0),
    mDimension(),
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

    CreateBuffer();
    CreateTexture();

    // NOTE(Wuxiang): Derived texture class should only bind specific texture type
    // and allocate texture storage.
}

PlatformTextureArray::~PlatformTextureArray()
{
    glDeleteBuffers(mDimension[2], mBufferObjList.data());
    glDeleteTextures(1, &mTextureObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTextureArray::Enable(Renderer *, int textureUnit, const TextureShaderMaskList&)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTextureObjPrevious = BindTexture(mTextureArrayPtr->GetTextureType(), mTextureObj);
}

void
PlatformTextureArray::Disable(Renderer *, int textureUnit, const TextureShaderMaskList&)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture(mTextureArrayPtr->GetTextureType(), mTextureObjPrevious);
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

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTextureArray::CreateBuffer()
{
    glGenBuffers(mDimension[2], mBufferObjList.data());
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTextureArrayPtr->GetTextureSlice(textureIndex);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
}

void
PlatformTextureArray::CreateTexture()
{
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTextureArrayPtr->GetTextureSlice(textureIndex);
        auto textureData = Map(nullptr, textureIndex,
                               ResourceMapAccessMode::WriteBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized, 0,
                               texture->mDataSize);
        memcpy(textureData, texture->mData, texture->mDataSize);
        Unmap(nullptr, textureIndex);
    }

    glGenTextures(1, &mTextureObj);
}


}

#endif