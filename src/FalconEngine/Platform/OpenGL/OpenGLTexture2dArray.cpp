#include <FalconEngine/Platform/OpenGL/OpenGLTexture2dArray.h>

#if defined(FALCON_ENGINE_API_OPENGL)

#include <cstring>

#include <FalconEngine/Platform/OpenGL/OpenGLUtility.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(Renderer *renderer, const Texture2dArray *textureArray) :
    PlatformTextureArray(renderer, textureArray)
{
    AllocateTexture();
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformTexture2dArray::AllocateTexture()
{
    GLuint textureBindingPrevious = BindTexture(mTextureArrayPtr->GetTextureType(), mTextureObj);

    // Allocate texture storage.
    {
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, mFormatInternal,
                       mDimension[0], mDimension[1], mDimension[2]);

        // Bind each texture slice to PBO.
        int textureArraySize = int(mDimension[2]);
        for (int textureIndex = 0; textureIndex < textureArraySize; ++textureIndex)
        {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, textureIndex,
                            mDimension[0], mDimension[1], 1,
                            mFormat, mType, nullptr);
        }

        // Unbind the PBO.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Restore previous texture binding
    BindTexture(mTextureArrayPtr->GetTextureType(), textureBindingPrevious);
}
}

#endif