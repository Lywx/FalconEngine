#include <FalconEngine/Platform/OpenGL/OpenGLTexture1dArray.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <cstring>

#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1dArray::PlatformTexture1dArray(Renderer *renderer, const Texture1dArray *textureArray) :
    PlatformTexture(renderer, textureArray)
{
    AllocateTexture();
}

PlatformTexture1dArray::~PlatformTexture1dArray()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture1dArray::AllocateTexture()
{
    // Bind newly created texture
    GLuint textureBindingPrevious = BindTexture(mTexturePtr->GetTextureType(), mTextureObj);

    // Allocate texture storage.
    {
        glTexStorage2D(GL_TEXTURE_1D_ARRAY, 1, mFormatInternal,
                       mDimension[0], mDimension[2]);

        // Bind each texture slice to PBO.
        int textureArraySize = int(mDimension[2]);
        for (int textureIndex = 0; textureIndex < textureArraySize; ++textureIndex)
        {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
            glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, textureIndex,
                            mDimension[0], 1,
                            mFormat, mType, nullptr);
        }

        // Unbind the PBO.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Restore previous texture binding
    BindTexture(mTexturePtr->GetTextureType(), textureBindingPrevious);
}
}

#endif