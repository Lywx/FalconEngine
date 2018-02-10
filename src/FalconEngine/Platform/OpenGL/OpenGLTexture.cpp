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
    mBufferObj(0),
    mTextureObj(0),
    mTextureObjPrevious(0),
    mTexturePtr(texture)
{
    mDimension[0] = texture->mDimension[0];
    mDimension[1] = texture->mDimension[1];
    mDimension[2] = texture->mDimension[2];

    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage(texture->mAccessMode, texture->mAccessUsage);

    CreateBuffer();
    CreateTexture();
}

PlatformTexture::~PlatformTexture()
{
    glDeleteBuffers(1, &mBufferObj);
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
PlatformTexture::Map(Renderer *, ResourceMapAccessMode access, ResourceMapFlushMode flush, ResourceMapSyncMode synchronization, int64_t offset, int64_t size)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    void *data = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, offset, size,
                                  OpenGLBufferAccessModeBit[int(access)] |
                                  OpenGLBufferFlushModeBit[int(flush)] |
                                  OpenGLBufferSynchronizationModeBit[int(synchronization)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    return data;
}

void
PlatformTexture::Unmap(Renderer *)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture::CreateBuffer()
{
    glGenBuffers(1, &mBufferObj);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, mTexturePtr->mDataSize, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void
PlatformTexture::CreateTexture()
{
    // NEW(Wuxiang): Add texture / image's write / read support.
    // NEW(Wuxiang): Add mipmap support.
    // int mipmapLevel = mTexturePtr->mMipmapLevel;

    // Fill in the texture data.
    void *textureData = Map(nullptr,
                            ResourceMapAccessMode::WriteBuffer,
                            ResourceMapFlushMode::Automatic,
                            ResourceMapSyncMode::Unsynchronized,
                            0,
                            mTexturePtr->mDataSize);
    memcpy(textureData, mTexturePtr->mData, mTexturePtr->mDataSize);
    Unmap(nullptr);

    // Generate texture object.
    glGenTextures(1, &mTextureObj);

    // NOTE(Wuxiang): Derived texture class should only bind specific texture type
    // and allocate texture storage.
}

}

#endif