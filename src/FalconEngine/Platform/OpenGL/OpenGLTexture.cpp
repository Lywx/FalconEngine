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
    mDimension(texture->GetDimension()),
    mMipmapLevel(texture->GetMipmapLevel()),
    mFormat(0),
    mFormatInternal(0),
    mType(0),
    mUsage(0)
{
    mType = OpenGLTextureType[TextureFormatIndex(texture->GetFormat())];
    mFormat = OpenGLTextureFormat[TextureFormatIndex(texture->GetFormat())];
    mFormatInternal = OpenGLTextureInternalFormat[TextureFormatIndex(texture->GetFormat())];
    mUsage = OpenGLBufferUsage(texture->GetAccessMode(), texture->GetAccessUsage());

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
        auto texture = mTexturePtr->GetSlice(textureIndex);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->GetDataSize(), nullptr, mUsage);
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
        auto texture = mTexturePtr->GetSlice(textureIndex);
        auto textureData = Map(nullptr, textureIndex,
                               ResourceMapAccessMode::WriteBuffer,
                               ResourceMapFlushMode::Automatic,
                               ResourceMapSyncMode::Unsynchronized, 0,
                               texture->GetDataSize());
        memcpy(textureData, texture->GetData(), texture->GetDataSize());
        Unmap(nullptr, textureIndex);
    }
}

}

#endif