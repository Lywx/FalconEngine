#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(GLuint textureTarget, const Texture *texture) :
    mTextureTarget(textureTarget),
    mTexturePtr(texture),
    mTextureObj(0),
    mTextureObjPrevious(0)
{
    mDimension[0] = texture->mDimension[0];
    mDimension[1] = texture->mDimension[1];
    mDimension[2] = texture->mDimension[2];

    mType = OpenGLTextureType[int(texture->mFormat)];
    mFormat = OpenGLTextureFormat[int(texture->mFormat)];
    mFormatInternal = OpenGLTextureInternalFormat[int(texture->mFormat)];
    mUsage = OpenGLBufferUsage[int(texture->mUsage)];

    glGenBuffers(1, &mBufferObj);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, texture->mDataSize, nullptr, mUsage);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Fill in the texture data
    void *textureData = Map(0, BufferAccessMode::Write);
    memcpy(textureData, texture->mData, texture->mDataSize);
    Unmap();

    // Allocate current texture memory
    {
        glGenTextures(1, &mTextureObj);

        // Bind newly created texture
        GLuint textureBindingPrevious = BindTexture(texture->mType, mTextureObj);

        {
            glTexStorage2D(mTextureTarget, 1, mFormatInternal, mDimension[0], mDimension[1]);

            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObj);
            glTexSubImage2D(mTextureTarget, 0, 0, 0, mDimension[0], mDimension[1],
                            mFormat, mType, nullptr);
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        }

        // Restore previous texture binding
        BindTexture(mTexturePtr->mType, textureBindingPrevious);
    }
}

PlatformTexture::~PlatformTexture()
{
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

}
