#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture2dArray.h>

#include <cstring>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLUtility.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(const Texture2dArray *textureArray) :
    PlatformTextureArray(textureArray)
{
    GLuint textureBindingPrevious = BindTexture(mTextureArrayPtr->mType, mTextureArrayObj);

    // Allocate texture storage.
    {
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, mFormatInternal,
                       mTextureArrayPtr->mDimension[0],
                       mTextureArrayPtr->mDimension[1],
                       mTextureArrayPtr->mDimension[2]);

        // Bind each texture slice to PBO.
        int textureArraySize = int(mDimensionList.size());
        for (int textureIndex = 0; textureIndex < textureArraySize; ++textureIndex)
        {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mBufferObjList[textureIndex]);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, textureIndex,
                            mDimensionList[textureIndex][0],
                            mDimensionList[textureIndex][1], 1,
                            mFormat, mType, nullptr);
        }

        // Unbind the PBO.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    // Restore previous texture binding
    BindTexture(mTextureArrayPtr->mType, textureBindingPrevious);
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
}

}

