#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTexture2dArray
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2dArray(const Texture2dArray *textures);
    ~PlatformTexture2dArray();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void *
    Map(int arrayIndex, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(int arrayIndex, int mipmapLevel);

private:
    std::vector<GLuint>   mBufferObjList;      // The buffer object for each slice of texture
    int                   mTextureArraySize;
    GLuint                mTextureObj;
    GLuint                mTextureObjPrevious;

    std::vector<Vector2i> mDimension;          // The dimension array for each slice of texture
    GLuint                mFormatInternal;
    GLuint                mFormat;
    GLuint                mType;
    GLuint                mUsage;
};
#pragma warning(default: 4251)

}
