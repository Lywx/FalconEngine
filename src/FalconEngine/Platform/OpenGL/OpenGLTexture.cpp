#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>
#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(const Texture *texture) :
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
    mUsage = OpenGLBufferUsage[int(texture->mUsage)];

    // NEW(Wuxiang): Add texture / image's write / read support.
    // NEW(Wuxiang): Add mipmap support.
    // int mipmapLevel = texture->mMipmapLevel;

    glGenBuffers(1, &mBufferObj);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Fill in the texture data.
    void *textureData = Map(BufferAccessMode::WriteBuffer,
                            BufferFlushMode::Automatic,
                            BufferSynchronizationMode::Unsynchronized,
                            0, texture->mDataSize);
    memcpy(textureData, texture->mData, texture->mDataSize);
    Unmap();

    // Generate texture object.
    glGenTextures(1, &mTextureObj);

    // NOTE(Wuxiang): Derived texture class should only bind specific texture type
    // and allocate texture storage.
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
PlatformTexture::Enable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    mTextureObjPrevious = BindTexture(mTexturePtr->mType, mTextureObj);
}

void
PlatformTexture::Disable(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture(mTexturePtr->mType, mTextureObjPrevious);
}

void *
PlatformTexture::Map(BufferAccessMode access, BufferFlushMode flush, BufferSynchronizationMode synchronization, int64_t offset, int64_t size)
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    void *data = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, offset, size,
                                  OpenGLBufferAccessModeMark[int(access)] |
                                  OpenGLBufferFlushModeMark[int(flush)] |
                                  OpenGLBufferSynchronizationModeMark[int(synchronization)]);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    return data;
}

void
PlatformTexture::Unmap()
{
    // NEW(Wuxiang): Add mipmap support.
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

}

#endif