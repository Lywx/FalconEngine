#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(Renderer *, const Texture *texture) :
    mTextureObj(0),
    mTextureObjPrevious(0),
    mTexturePtr(texture),
    mDimension(),
    mFormat(0),
    mFormatInternal(0),
    mType(0),
    mUsage(0)
{
    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage(texture->mAccessMode, texture->mAccessUsage);

    mDimension = texture->mDimension;
    mBufferObjList.assign(mDimension[2], 0);

    CreateBuffer();
    AllocateBuffer();
    FillBuffer();

    CreateTexture();

    // NOTE(Wuxiang): Derived texture class should only bind specific texture type
    // and allocate texture storage.
}

PlatformTexture::~PlatformTexture()
{
    glDeleteBuffers(mDimension[2], mBufferObjList.data());
    glDeleteTextures(1, &mTextureObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture::Enable(Renderer *, int textureUnit, const TextureShaderMaskList&)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTextureObjPrevious = BindTexture(mTexturePtr->GetTextureType(), mTextureObj);
}

void
PlatformTexture::Disable(Renderer *, int textureUnit, const TextureShaderMaskList&)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture(mTexturePtr->GetTextureType(), mTextureObjPrevious);
}

void *
PlatformTexture::Map(Renderer *renderer, ResourceMapAccessMode access, ResourceMapFlushMode flush,
                     ResourceMapSyncMode sync, int64_t offset, int64_t size)
{
    return Map(renderer, 0, access, flush, sync, offset, size);
}

void *
PlatformTexture::Map(Renderer *,
                     int textureIndex,
                     ResourceMapAccessMode access,
                     ResourceMapFlushMode flush,
                     ResourceMapSyncMode sync,
                     int64_t offset,
                     int64_t size)
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    void *data = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, offset, size,
                                  OpenGLBufferAccessModeBit[int(access)] |
                                  OpenGLBufferFlushModeBit[int(flush)] |
                                  OpenGLBufferSynchronizationModeBit[int(sync)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    return data;
}

void
PlatformTexture::Unmap(Renderer *renderer)
{
    Unmap(renderer, 0);
}

void
PlatformTexture::Unmap(Renderer *, int textureIndex)
{
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
PlatformTexture::AllocateBuffer()
{
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTexturePtr->GetTextureSlice(textureIndex);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
}

void
PlatformTexture::CreateBuffer()
{
    glGenBuffers(mDimension[2], mBufferObjList.data());
}

void
PlatformTexture::CreateTexture()
{
    glGenTextures(1, &mTextureObj);
}

void
PlatformTexture::FillBuffer()
{
    for (int textureIndex = 0; textureIndex < mDimension[2]; ++textureIndex)
    {
        auto texture = mTexturePtr->GetTextureSlice(textureIndex);
        auto textureData = Map(nullptr, textureIndex,
                               ResourceMapAccessMode::WriteBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized, 0,
                               texture->mDataSize);
        memcpy(textureData, texture->mData, texture->mDataSize);
        Unmap(nullptr, textureIndex);
    }
}

}

#endif